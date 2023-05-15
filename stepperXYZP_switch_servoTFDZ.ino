#include "stepperXYZP.h"
#include "servoTFDZ.h"

//Other Inputs
#define MISC_INPUTS_REFRESH_MS 100
const int stepperSpeedPot = A8;
const int switchAup = 53;
const int switchAdown = 41;

//Steppers
#define NUM_OF_STEPPERS 4
//switchUp, switchDown, dirPin, stepPin
MyStepper stepperX(45, 33, 5, 2);
MyStepper stepperY(47, 35, 6, 3);
MyStepper stepperZ(49, 37, 7, 4);
MyStepper stepperP(51, 39, 13, 12);
MyStepper steppers[NUM_OF_STEPPERS] = {stepperX, stepperY, stepperZ, stepperP};

//Servos
#define NUM_OF_SERVOS 4 
Servo srvT;
Servo srvF;
Servo srvD;
Servo srvZ;

//servo, readPin, servoPin
MyServo servoT(srvT, 9, 14);
MyServo servoF(srvF, 10, 15);
MyServo servoD(srvD, 11, 16);
MyServo servoZ(srvZ, 12, 17);
MyServo servos[NUM_OF_SERVOS] = {servoT, servoF, servoD, servoZ};

//Gates and timer 
bool stepperGate = false;
bool servoGate = false;
unsigned long miscTimer = 0;
int stepDelay = 0;

void setup() {
  //Stepper pins
  for (int i = 0; i < NUM_OF_STEPPERS; i++){
    steppers[i].pinInit();
  }
  //Stepper speed control
  pinMode(stepperSpeedPot, INPUT);

  //Servo Pins
  for (int i = 0; i < NUM_OF_SERVOS; i++){
    servos[i].pinInit();
  }
  //Switch Pins
	pinMode(switchAup, INPUT_PULLUP);
	pinMode(switchAdown, INPUT_PULLUP);
}


void loop() {
  //Only read every x ms
  unsigned int now = millis();
  if (now - miscTimer > MISC_INPUTS_REFRESH_MS){
    stepperGate = digitalRead(switchAup);
    servoGate = digitalRead(switchAdown);
    stepDelay = map(analogRead(stepperSpeedPot), 0, 1023, 0, 1000);
    miscTimer = now;
  }

  //Run all steppers
  if(stepperGate){  
    for (int i = 0; i < NUM_OF_STEPPERS; i++){
      steppers[i].read(MISC_INPUTS_REFRESH_MS);
      steppers[i].run(stepDelay);
    }
	}
  //Run all servos
	if(servoGate){
    for (int i = 0; i < NUM_OF_SERVOS; i++){
      servos[i].read(MISC_INPUTS_REFRESH_MS);
      servos[i].run();
    }
	}
}
