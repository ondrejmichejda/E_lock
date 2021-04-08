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
	Time _time;
	int _ms;
	int _msOld;
	int _msSum;
	bool blink;

public:
	Display(int pin1, int pin2):_display(pin1, pin2){
		_display.setBrightness(1);
		_display.clear();
	}
	bool EditMode;
	bool PwdMode;

	void Update(Time time){
		_time = time;
		_display.showNumberDec(_time.getMinute(), true, 2, 2);
		_display.showNumberDecEx(_time.getHour(), 0b01000000, true, 2, 0);	
	}

	void Update(){
		_display.showNumberDec(_time.getMinute(), true, 2, 2);
		_display.showNumberDecEx(_time.getHour(), 0b01000000, true, 2, 0);
		
	}
	
	void Run(){
		_ms = millis();
		if(EditMode){
			_msSum += _ms - _msOld;
			if(_msSum > BLINKTIME){
				_msSum = 0;
				if(blink)
					_display.clear();
				else	
					Update(_time);

				blink = !blink;
			}
		}
		else if(PwdMode){
			_display.clear();
		}
		else{
			_msSum = 0;
		}
		_msOld = _ms;
	}
};

#endif