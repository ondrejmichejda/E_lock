/*
  Relay.h - Simple 1 channel relay.
*/

#ifndef Relay_h
#define Relay_h

#include "Arduino.h"

class Relay
{
private:
    uint8_t _pin;

public:
    Relay(uint8_t pin){
        _pin = pin;
        pinMode(_pin, OUTPUT);
    }

    void Close(){
        digitalWrite(_pin, LOW);
    }

    void Open(){
        digitalWrite(_pin, HIGH);
    }

};

#endif