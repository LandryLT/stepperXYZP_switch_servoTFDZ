#include "servoTFDZ.h"

//My Servo Constructor
MyServo::MyServo(Servo servo, int readPin, int servoPin) {
  //Declare external variables
  _readPin = readPin;
  _servo = servo;
  _servoPin = servoPin;

  //Init internal variables
  _internalTimer = 0;
  _val = 0;
}

//Init Pins
void MyServo::pinInit() {
  _servo.attach(_servoPin);
  pinMode(_readPin, INPUT);
}

//Only read ever x milliseconds
void MyServo::read(int delay) {
  unsigned long now = millis();
  if (now - _internalTimer > delay)
  {
    _val = map(analogRead(_readPin), 0, 1023, 0, 179);
    _internalTimer = now;
  }
}


//Only write if value has changed
void MyServo::run() {
  if (_val != _last_val)
  {
    _servo.write(_val);
    _last_val = _val;
  }
}