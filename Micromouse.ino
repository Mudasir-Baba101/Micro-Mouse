#include "floodfill.h"


void setup() {
  
  floodfillInit();
}

void loop() {

  bool f = wallFront(); // wall detection, either ir or ultrasonic or tof idk
  bool l = wallLeft();
  bool r = wallRight();

  while (!floodfillAtGoal()) {
    floodfillUpdateWalls(f, l, r);

    Dir next = floodfillNextMove();

    turnTo(next);          // motor stuff to turn, also will add mpu6050
    moveOneCell();         // encoders will ensure that it moves exactly 1 cell hopefully

    floodfillSetHeading(next);
    floodfillAdvance();
  }
}

bool wallFront();
bool wallRight();
bool wallFront();
void turnTo(Dir d);
void moveOneCell();

