#include <Wire.h>

#define MPU_ADDR 0x68
#define GYRO_ZOUT_H 0x47

// ----- Tunables -----
#define GYRO_SENS 131.0      // LSB/(deg/s) for ±250 dps
#define CALIB_SAMPLES 3000
#define LPF_ALPHA 0.95       // closer to 1 = smoother, less noise

float gyroBiasZ = 0.0;
float yaw = 0.0;
float gyroZFiltered = 0.0;

unsigned long lastMicros;

int16_t readGyroZ() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(GYRO_ZOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 2, true);
  return (Wire.read() << 8) | Wire.read();
}

void calibrateGyro() {
  long sum = 0;
  for (int i = 0; i < CALIB_SAMPLES; i++) {
    sum += readGyroZ();
    delayMicroseconds(1000);
  }
  gyroBiasZ = (float)sum / CALIB_SAMPLES;
}

void setup() {
  Serial.begin(115200);

  Wire.begin(22, 23);   // SDA = 22, SCL = 23
  Wire.setClock(400000);

   Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);     // PWR_MGMT_1
  Wire.write(0x00);
  Wire.endTransmission();

  delay(100);
  calibrateGyro();

  lastMicros = micros();
}

void loop() {
  unsigned long now = micros();
  float dt = (now - lastMicros) * 1e-6;
  lastMicros = now;

  int16_t rawGz = readGyroZ();
  float gyroZ = (rawGz - gyroBiasZ) / GYRO_SENS;

  // Low-pass filter
  gyroZFiltered = LPF_ALPHA * gyroZFiltered + (1.0 - LPF_ALPHA) * gyroZ;

  yaw += gyroZFiltered * dt;

  Serial.println(yaw);

  delay(2);
}
