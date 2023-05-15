#ifndef STEPPERTFDZ_H
#define STEPPERTFDZ_H

#include <Servo.h>
#include <Arduino.h>
#include "serialDebugger.h"

class MyServo
{
private:
  int _readPin;
  int _servoPin;
  int _val;
  int _last_val;
  unsigned long _internalTimer;
  Servo _servo;
public:
  serialDebugger debugger = serialDebugger(false);
  void read(int delay);
  void run();
  void pinInit();
  MyServo(Servo servo, int readPin, int servoPin, bool debug = false);
};

#endif