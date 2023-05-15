# stepperXYZP_switch_servoTFDZ

**stepperXYZP_switch_servoTFDZ** is an Arduino project to control multiple stepper and servo motors.

---
## main loops
- ```loopInOrder()``` reads on all misc inputs, then takes care of all stepper motors and ends with all servo motors per cycle. All methods are non blocking so, in practice, every task will be done if due time is expired with respects to the order mentionned above.
- ```loopInTurn()``` takes care of a single stepper, then a single servo and ends with reading all misc inputs per cycle. All methods are non blocking so, in practice, every task will be done if due time is expired with respects to the order mentionned above.
---
## servoTFDZ 

**MyServo** is a class to control a servo motor's rotation speed.
```c++
class MyServo
{
    public:
        //Constructor: needs Servo object, speed input pin and servo output pin
        MyServo(Servo servo, int readPin, int servoPin);
        //Initialise pins
        void pinInit();
        //Non-blocking read potentiometer for speed control
        void read(int delay);
        //Write on output pin only if value has changed
        void run();
};

```

---

## stepperXYZP

**MyStepper** is a class to control a stepper motor's rotation speed.
```c++
class MyStepper
{
    public:
        /*Constructor: needs switch up and switch down input pins, as well as the stepper's direction and
        step output pins.*/
        MyStepper(int switchUp, int switchDown, int dirPin, int stepPin);
        //Initialise pins
        void pinInit();
        //Read switchs up and down
        void read(int delay_ms);
        //Non-blocking constant spinning driver
        void run(int stepdelay);
};
```
Here's a detail on the ```MyStepper::run(int stepdelay)``` method:
```c++
void MyStepper::run(int stepdelay) {
    //Default LOW, change direction if switch is set to down :
    bool dir = LOW;
    if (_switchDownState)  {dir = HIGH;}
    
    //Write on dirPin only if directions has changed
    if (dir != _lastDir)  {
        digitalWrite(_dirPin, dir);
        _lastDir = dir;
    }

    //Non-blocking stepper speed control
    unsigned long now = micros();
    //If either switch state is active
    if(_switchUpState || _switchDownState)  {
        //If too many micros have gone by, set internal timer back to 0
        if (_internalTimer > now)  {_internalTimer = 0;}
        //Alternate stepper state if enough time has gone by
        if (now - _internalTimer >= stepdelay)  {
            digitalWrite(_stepPin, !_lastState);
            _lastState = !_lastState;
            _internalTimer = now;
        }
    } else {
        //Change stepper state to low only if it's not already the case
        if (_lastState != LOW) {
            digitalWrite(_stepPin, LOW);
        }
    }
}

```
