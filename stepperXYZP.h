#ifndef STEPPERXYZP_h
#define STEPPERXYZP_h

#include <Arduino.h>

class MyStepper
{
  private:
    unsigned long _internalTimer;
    unsigned long _internalReadTimer;
    int _switchUpState;
    int _switchDownState;
    bool _lastDir;
    bool _lastState;
    int _switchUp;
    int _switchDown;
    int _dirPin;
    int _stepPin;
  public:
    void read(int delay_ms);
    void run(int stepdelay);
    void pinInit();
    MyStepper(int switchUp, int switchDown, int dirPin, int stepPin);
};

#endif