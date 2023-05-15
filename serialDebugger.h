#ifndef SERIALDEBUGGER_H
#define SERIALDEBUGGER_H

#include <Arduino.h>

class serialDebugger
{
private:
    bool _active;
public:
    serialDebugger(bool isActive);
    void setActive(bool isActive);
    bool getActive();
    void serialInit(int baudRate);
    void serialPrint(String label, String value, bool carry = true);
};

#endif