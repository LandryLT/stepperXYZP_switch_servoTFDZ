#include "serialDebugger.h"

//Debug
serialDebugger::serialDebugger(bool isActive)
{
    _active = isActive;
}

//Get/Set private active value
void serialDebugger::setActive(bool isActive){
    _active = isActive;
}
bool serialDebugger::getActive(){
    return _active;
}

//Print something
void serialDebugger::serialPrint(String label, String value, bool carry = true){
    //Do nothing
    if (!_active){
        return;
    }
    //Print something
    if (carry){
        Serial.println(label + value);
    } else {
        Serial.print(label + value + "\t");
    }
}

