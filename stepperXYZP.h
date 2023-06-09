#ifndef STEPPERXYZP_h
#define STEPPERXYZP_h

#include <Arduino.h>
#include "serialDebugger.h"

class MyStepper
{
  private:
    unsigned long _internalTimer;
    unsigned long _internalReadTimer;
    bool _switchUpState;
    bool _switchDownState;
    bool _lastDir;
    bool _lastState;
    int _switchUpPin;
    int _switchDownPin;
    int _dirPin;
    int _stepPin;
  public:
    serialDebugger debugger = serialDebugger(false);
    void read(int delay_ms);
    void run(int stepdelay);
    void pinInit();
    MyStepper(int switchUpPin, int switchDownPin, int dirPin, int stepPin, bool debug = false);
};

#endif