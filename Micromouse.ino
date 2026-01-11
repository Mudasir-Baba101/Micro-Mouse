#include "floodfill.h"

const int r_trigPin = 5;
const int r_echoPin = 18;

const int l_trigPin = 14;
const int l_echoPin = 32;

const int f_trigPin = 21;
const int f_echoPin = 19;

#define SOUND_SPEED 0.034
#define WALL_DIST 10.00

long duration;
float distanceCm;

void setup() {
  // put your setup code here, to run once:
  pinMode(r_trigPin, OUTPUT); 
  pinMode(r_echoPin, INPUT); 
  pinMode(l_trigPin, OUTPUT); 
  pinMode(l_echoPin, INPUT); 
  pinMode(f_trigPin, OUTPUT); 
  pinMode(f_echoPin, INPUT); 
  floodfillInit();
}

void loop() {

  bool F = wallFront(); // wall detection, either ir or ultrasonic or tof idk
  bool L = wallLeft();
  bool R = wallRight();


  // while (!floodfillAtGoal()) {
  //   floodfillUpdateWalls(f, l, r);

  //   Dir next = floodfillNextMove();

  //   turnTo(next);          // motor stuff to turn, also will add mpu6050
  //   moveOneCell();         // encoders will ensure that it moves exactly 1 cell hopefully

  //   floodfillSetHeading(next);
  //   floodfillAdvance();
  // }

  if (!L) {
    // No wall on left → hug left
    turnLeft();
    delay(150);           // allow turn to complete
    moveForward();
  }
  else if (F) {
    turnRight();
    delay(150);
    moveForward();
  }
  else {
    moveForward();
  }

  delay(20);  
}

}


bool wallLeft() {
  digitalWrite(l_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(l_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(l_trigPin, LOW);
  
  duration = pulseIn(l_echoPin, HIGH);
  
  distanceCm = duration * SOUND_SPEED/2;

  if(distanceCm < WALL_DIST)
    return true;
  return false;
}

bool wallFront() {
  digitalWrite(f_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(f_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(f_trigPin, LOW);
  
  duration = pulseIn(f_echoPin, HIGH);
  
  distanceCm = duration * SOUND_SPEED/2;

  if(distanceCm < WALL_DIST)
    return true;
  return false;
}

bool wallRight() {
  digitalWrite(r_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(r_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(r_trigPin, LOW);
  
  duration = pulseIn(r_echoPin, HIGH);
  
  distanceCm = duration * SOUND_SPEED/2;

  if(distanceCm < WALL_DIST)
    return true;
  return false;
}

// void turnTo(Dir d);
// void moveOneCell();


