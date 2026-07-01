#include <Arduino.h>
#include <battle-bots-lib.h>
#include <Stepper.h>

const int DEADBAND = 20;
Motor input1(1, DEADBAND, 130, 255); // elevator — forward/back
Motor input2(0, DEADBAND, 130, 255); // aileron  — left/right turn
Switch input3(4, false);             // switch   — stepper on/off

// L9110 pin pairs (A=forward side, B=reverse side)
const int LEFT_A  = 3;
const int LEFT_B  = 5;
const int RIGHT_A = 6;
const int RIGHT_B = 9;

// Stepper (28BYJ-48 via ULN2003/XJS9471E4) — pins 10=IN1, 11=IN2, 12=IN3, 13=IN4
// Negate stepperSpeed to reverse direction
const int STEPS_PER_REV = 2048;
int stepperSpeed = 10; // RPM; negative = reverse
Stepper stepper(STEPS_PER_REV, 10, 12, 11, 13); // IN1, IN3, IN2, IN4 order for 28BYJ-48

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
  Serial.begin(9600);
  pinMode(LEFT_A,  OUTPUT);
  pinMode(LEFT_B,  OUTPUT);
  pinMode(RIGHT_A, OUTPUT);
  pinMode(RIGHT_B, OUTPUT);
  stepper.setSpeed(abs(stepperSpeed));
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

  if (input3.getValue() == 1) {
    stepper.step(stepperSpeed > 0 ? 1 : -1);
  }
}
