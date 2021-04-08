/*
  Key.h - Library for handle key of keyboard.
*/
#ifndef PulseGenerator_h
#define PulseGenerator_h

#include "Arduino.h"

class PulseGenerator
{
public:
	PulseGenerator(long ms){
        _ms = ms;           
    }
    bool On(){
        _millis = millis();
        _time += _millis - _millisOld;
        _millisOld = _millis;

        if(_time >= _ms){
            _time = 0;
            return true;
        }
        else{
            return false;
        }
    }

    void reset(){
        _time = 0;
    }
private:
    long _ms;
	long _time;
    long _millisOld;
    long _millis;
};

#endif