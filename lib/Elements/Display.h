/*
  Display.h - Library for handle Display of Displayboard.
*/
#ifndef Display_h
#define Display_h

#define BLINKTIME 250

#include "Arduino.h"
#include "TM1637Display.h"
#include "Time.h"

class Display
{
private:
	TM1637Display _display;
	int _ms;
	int _msOld;
	int _msSum;
	bool _blink;

public:
	Display(int pin1, int pin2):_display(pin1, pin2){
		_display.setBrightness(1);
		_display.clear();

		_ms = 0;
		_msOld = 0;
		_msSum = 0;
		_blink = false;
	}
	bool EditMode;
	bool PwdMode;

	void Update(Time time){
		_display.showNumberDec(time.GetMinute(), true, 2, 2);
		_display.showNumberDecEx(time.GetHour(), 0b01000000, true, 2, 0);	
	}
	
	void Run(Time time){
		/*_ms = millis();
		if(EditMode){
			_msSum += _ms - _msOld;
			if(_msSum > BLINKTIME){
				_msSum = 0;
				if(_blink)
					_display.clear();
				else	
					Update(time);

				_blink = !_blink;
			}
		}
		else if(PwdMode){
			_display.clear();
		}
		else{
			_msSum = 0;
		}
		_msOld = _ms;*/
	}
};

#endif