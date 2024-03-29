/*
  TOn.h
*/
#ifndef TOn_h
#define TOn_h

#include "Arduino.h"

//! Timer On class.
class TOn
{
private:
    long _time;
    int _oldMs;
    int _actMs;

public:
    //! Input.
	bool In;

    //! Output - is true after preset time if Input is TRUE.
    bool Out;

    //! Elapsed time till output is activated.
    int Elapsed;

    //! Initialize timer on class.
    //! @param t Preset time after which Out is set.
	TOn(long t){
        _time = t;
        _oldMs = 0;
        _actMs = 0;

        // parameter init
        In = false;
        Out = false;
        Elapsed = 0;
    };

    //! Main function for object functionality (must be called).
    void Run(){
        _actMs = millis();
        if(In)
        {
            Elapsed += _actMs - _oldMs;
            Out = Elapsed >= _time;
        }
        else
        {
            Out = false;
            Elapsed = 0;
        }
        _oldMs = _actMs;
    }

    // Reinitializes all inputs and outputs.
    void ReInit(){
        In = false;
        Out = false;
        Elapsed = 0;
    }
};

#endif