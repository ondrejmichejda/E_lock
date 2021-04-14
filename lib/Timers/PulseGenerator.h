/*
  Key.h - Library for handle key of keyboard.
*/
#ifndef PulseGenerator_h
#define PulseGenerator_h

#include "Arduino.h"

//! Pulse Generator object.
class PulseGenerator
{
private:
    long _ms;
	long _time;
    long _millisOld;
    long _millis;

public:
    //! Initializes PulseGenerator object.
    //! @param ms Frequency in miliseconds.
    //!
	PulseGenerator(long ms){
        _ms = ms;           
        _time = 0;
        _millisOld = 0;
        _millis = 0;
    }

    //! Work function
    //! @return TRUE if pulse.
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

    //! Reseting generator.
    void Reset(){
        _time = 0;
    }
};

#endif