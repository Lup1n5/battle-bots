#include <Arduino.h>
#include <battle-bots-lib.h>

const int DEADBAND = 20;
Motor input1(1, DEADBAND, 130, 255); // elevator — forward/back
Motor input2(0, DEADBAND, 130, 255); // aileron  — left/right turn

// L9110 pin pairs (A=forward side, B=reverse side)
const int LEFT_A  = 3;
const int LEFT_B  = 5;
const int RIGHT_A = 6;
const int RIGHT_B = 9;

void driveMotor(int pinA, int pinB, int speed) {
  if (speed > 0) {
    analogWrite(pinA, speed);
    analogWrite(pinB, 0);
  } else if (speed < 0) {
    analogWrite(pinA, 0);
    analogWrite(pinB, -speed);
  } else {
    analogWrite(pinA, 0);
    analogWrite(pinB, 0);
  }
}

void setup() {
  pinMode(LEFT_A,  OUTPUT);
  pinMode(LEFT_B,  OUTPUT);
  pinMode(RIGHT_A, OUTPUT);
  pinMode(RIGHT_B, OUTPUT);
}

void loop() {
  int fwd  = input1.getOutput(); // positive = forward,    negative = back
  int turn = input2.getOutput(); // positive = right turn, negative = left turn

  int leftSpeed  = fwd + turn;
  int rightSpeed = fwd - turn;

  int maxMag = max(abs(leftSpeed), abs(rightSpeed));
  if (maxMag > 255) {
    leftSpeed  = leftSpeed  * 255 / maxMag;
    rightSpeed = rightSpeed * 255 / maxMag;
  }

  driveMotor(LEFT_A,  LEFT_B,  leftSpeed);
  driveMotor(RIGHT_B, RIGHT_A, rightSpeed); // pins swapped — motor is mirrored on right side
}
