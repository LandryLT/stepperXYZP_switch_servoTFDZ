#include "stepperXYZP.h"

//My Stepper Constructor
MyStepper::MyStepper(int switchUp, int switchDown, int dirPin, int stepPin) {
  //Declare pins
  _switchUp = switchUp;
  _switchDown= switchDown;
  _dirPin = dirPin;
  _stepPin = stepPin;

  //Init internal variables
  _switchUpState = LOW;
  _switchDownState = LOW;
  _lastDir = LOW;
  _lastState = LOW;
  _internalTimer = 0;
  _internalReadTimer = 0;
}

//Init Pins
void MyStepper::pinInit() {
  pinMode(_dirPin, OUTPUT);
  pinMode(_stepPin, OUTPUT);
  pinMode(_switchUp, INPUT_PULLUP);
  pinMode(_switchDown, INPUT_PULLUP);
}

void MyStepper::read(int delay_ms) {
  unsigned long now = millis();
  if (now - _internalReadTimer > delay_ms){
    _switchUpState = digitalRead(_switchUp);
    _switchDownState = digitalRead(_switchDown);
  }
}

void MyStepper::run(int stepdelay) {
  //Get directions right
  bool dir = LOW;
  if (_switchDownState)
  {
    dir = HIGH;
  }

  //Write on dirPin only if directions has changed
  if (dir != _lastDir)
  {
    digitalWrite(_dirPin, dir);
    _lastDir = dir;
  }

  //Non-blocking stepper speed control
  unsigned long now = micros();
  if(_switchUpState || _switchDownState)
  {

    //If too many micros have gone by, set internal timer back to 0
    if (_internalTimer > now)
    {
      _internalTimer = 0;
    }

    //Change stepper state enough time has gone by
    if (now - _internalTimer >= stepdelay)
    {
      digitalWrite(_stepPin, !_lastState);
      _lastState = !_lastState;
      _internalTimer = now;
    }
	} 
  else 
  {

    //Change stepper state to low only if necessary
    if (_lastState != LOW)
    {
      digitalWrite(_stepPin, LOW);
    }
	}
}
