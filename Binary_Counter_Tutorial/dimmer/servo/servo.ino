#include <Servo.h>

#define servoPin 10

Servo myServo;

int position = 180;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  myServo.write(position);
}
