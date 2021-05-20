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
    bool _opened;
    bool _closed;

public:
    Relay(uint8_t pin){
        _pin = pin;
        _timer = new TOn(5000);
        _opened = false;
        _closed = false;
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

    void Open(){
        digitalWrite(_pin, HIGH);
        _opened = true;
    }

    void Close(){
        digitalWrite(_pin, LOW);
        _timer->In = true;
        _closed = true;
    }

    bool Opened(){
        bool result = _opened;
        _opened = false;
        return result;
    }

    bool Closed(){
        bool result = _closed;
        _closed = false;
        return result;
    }

};

#endif