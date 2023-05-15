#include "stepperXYZP.h"

//My Stepper Constructor
MyStepper::MyStepper(int switchUpPin, int switchDownPin, int dirPin, int stepPin, bool debug=false) {
  //Declare pins
  _switchUpPin = switchUpPin;
  _switchDownPin= switchDownPin;
  _dirPin = dirPin;
  _stepPin = stepPin;
  debugger.setActive(debug);

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
  pinMode(_switchUpPin, INPUT_PULLUP);
  pinMode(_switchDownPin, INPUT_PULLUP);

  //DEBUG-------------------------------------------------------------------
  debugger.serialPrint("STEP PIN INIT:\tdirPin:\t", String(_dirPin), false);
  debugger.serialPrint("stepPin:\t", String(_stepPin), false);
  debugger.serialPrint("switchUpPin:\t", String(_switchUpPin), false);
  debugger.serialPrint("switchDownPin:\t", String(_switchDownPin));
  //DEBUG-------------------------------------------------------------------
}

void MyStepper::read(int delay_ms) {
  unsigned long now = millis();
  if (now - _internalReadTimer > delay_ms){
    _switchUpState = digitalRead(_switchUpPin);
    _switchDownState = digitalRead(_switchDownPin);

    //DEBUG-------------------------------------------------------------------
    debugger.serialPrint("STEP SWITCH UP ", String(_switchUpPin) + ":", false);
    debugger.serialPrint("", String(_switchUpState));
    debugger.serialPrint("STEP SWITCH DOWN ", String(_switchDownPin) + ":", false);
    debugger.serialPrint("", String(_switchDownState));
    //DEBUG-------------------------------------------------------------------
  }
}

void MyStepper::run(int stepdelay) {
  //If switch is either up and down, or neither up nor down, set step pin to LOW and return
  if (_switchUpState == _switchDownState){
    //Change stepper state to low only if necessary
    if (_lastState != LOW)
    {
      digitalWrite(_stepPin, LOW);
      _lastState = LOW;      
    }

    //DEBUG-------------------------------------------------------------------
    debugger.serialPrint("STEPPER ", String(_stepPin) + " STOP");
    //DEBUG-------------------------------------------------------------------
    return;
  }

  
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

    //DEBUG-------------------------------------------------------------------
    debugger.serialPrint("STEPPER ", String(_stepPin) + " CHANGED DIRECTION :", false);
    debugger.serialPrint("", String(_lastDir));
    //DEBUG-------------------------------------------------------------------
  }

  //Non-blocking stepper speed control
  unsigned long now = micros();
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
    
    //DEBUG-------------------------------------------------------------------
    debugger.serialPrint("STEPPER ", String(_stepPin) + " is changing state every:", false);
    debugger.serialPrint("", String(stepdelay));
    //DEBUG-------------------------------------------------------------------
  } 
}
