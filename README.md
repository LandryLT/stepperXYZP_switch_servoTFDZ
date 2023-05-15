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
        //Optionnal debug flag
        MyServo(Servo servo, int readPin, int servoPin, bool debug = false);
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
        step output pins.
        Optionnal debug flag*/
        MyStepper(int switchUpPin, int switchDownPin, int dirPin, int stepPin, bool debug = false);
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
    //If switch is either up and down, or neither up nor down, set step pin to LOW and do nothing
    if (_switchUpState == _switchDownState){
        //Change stepper state to low only if it's not already the case
        if (_lastState != LOW) {
            digitalWrite(_stepPin, LOW);
            _lastState = LOW;
        }
        //Do nothing
        return;
    }
    //Do something ->
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
    //If too many micros have gone by, set internal timer back to 0
    if (_internalTimer > now)  {_internalTimer = 0;}
    //Alternate stepper state if enough time has gone by
    if (now - _internalTimer >= stepdelay)  {
        digitalWrite(_stepPin, !_lastState);
        _lastState = !_lastState;
        _internalTimer = now;
    }
}

```
---

## serialDebugger

**serialDebugger** is a class to control debug messages on Serial port.
```c++
class serialDebugger
{
public:
    //Constructor, declare initial state
    serialDebugger(bool isActive);
    //Get set active state
    void setActive(bool isActive);
    bool getActive();
    //Initiate Serial.begin()
    void serialInit(int baudRate);
    //Print stuff if active
    void serialPrint(String label, String value, bool carry = true);
};
```