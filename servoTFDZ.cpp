#include "servoTFDZ.h"

//My Servo Constructor
MyServo::MyServo(Servo servo, int readPin, int servoPin, bool debug = false) {
  //Declare external variables
  _readPin = readPin;
  _servo = servo;
  _servoPin = servoPin;
  debugger.setActive(debug);

  //Init internal variables
  _internalTimer = 0;
  _val = 0;
}

//Init Pins
void MyServo::pinInit() {
  _servo.attach(_servoPin);
  pinMode(_readPin, INPUT);

  //DEBUG-------------------------------------------------------------------
  debugger.serialPrint("SERVO PIN INIT:\twrite\t", String(_servoPin), false);
  debugger.serialPrint("read:\t", String(_readPin));
  //DEBUG-------------------------------------------------------------------
}

//Only read ever x milliseconds
void MyServo::read(int delay) {
  unsigned long now = millis();
  if (now - _internalTimer > delay)
  {
    _val = map(analogRead(_readPin), 0, 1023, 0, 179);
    _internalTimer = now;
    
    //DEBUG-------------------------------------------------------------------
    debugger.serialPrint("SERVO READ ", String(_readPin) + ":", false);
    debugger.serialPrint("", String(_val));
    //DEBUG-------------------------------------------------------------------
  }
}


//Only write if value has changed
void MyServo::run() {
  if (_val != _last_val)
  {
    _servo.write(_val);
    _last_val = _val;

    //DEBUG-------------------------------------------------------------------
    debugger.serialPrint("SERVO WRITE ", String(_servoPin) + ":", false);
    debugger.serialPrint("", String(_val));
    //DEBUG-------------------------------------------------------------------
  }
}