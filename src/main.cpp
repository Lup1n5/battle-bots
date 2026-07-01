#include <Arduino.h>
#include <battle-bots-lib.h>
const int DEADBAND = 1;
Motor input1(1, 20, 130, 255); //ele
Motor input2(2, 20, 130, 255); //ail
Motor input3(3, 20, 130, 255); 
Motor input4(4, 20, 130, 255);
Motor input5(5, 20, 130, 255);
Motor input6(6, 20, 130, 255);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  
}

void loop() {
  //Serial.print(motor1.getJoystickValue() + "    ");
  //delay(0.03);
  int speed = input1.getOutput();
  //Serial.println(speed);
  if (speed == 0) {
  analogWrite(8,0);
  analogWrite(9,0); 
  } 
//  else {
//    analogWrite(8,speed);
//    analogWrite(9,0);
//    }
   
    else if (speed >0) {
    analogWrite(8,speed);
    analogWrite(9,0);
  } else {
    analogWrite(8,0);
    analogWrite(9,abs(speed));
  }
}