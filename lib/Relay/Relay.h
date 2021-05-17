/*
  Relay.h - Simple 1 channel relay.
*/

#ifndef Relay_h
#define Relay_h

#include "Arduino.h"
#include "TOn.h"

class Relay
{
private:
    uint8_t _pin;
    TOn* _timer;

public:
    Relay(uint8_t pin){
        _pin = pin;
        _timer = new TOn(5000);
        pinMode(_pin, OUTPUT);
        Open();
    }

    void Run(){
        _timer->Run();

        if(_timer->Out ){
            _timer->In = false;
            Open();
        }
    }

    void Close(){
        digitalWrite(_pin, LOW);
        _timer->In = true;
    }

    void Open(){
        digitalWrite(_pin, HIGH);
    }

};

#endif