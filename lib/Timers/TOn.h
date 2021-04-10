/*
  TOn.h
*/
#ifndef TOn_h
#define TOn_h

#include "Arduino.h"

class TOn
{
private:
    int _time;
    int _oldMs;
    int _actMs;

public:
	TOn(int t){
        _time = t;
        In = false;
        Out = false;
        Elapsed = 0;
    };
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

	bool In;
    bool Out;
    int Elapsed;
};

#endif