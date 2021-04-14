/*
  Display.h - Library for handle Display of Displayboard.
*/
#ifndef Display_h
#define Display_h

#define BLINKTIME 250

#include "Arduino.h"
#include "TM1637Display.h"
#include "Time.h"

//! Wrapping class for TM1637 display.
class Display
{
private:
	TM1637Display* _display = NULL;
	int _ms;
	int _msOld;
	int _msSum;
	bool _blink;

public:
	//! Initialize display TM1637 wrapper.
	//! @param pinClk The number of the digital pin connected to the clock pin of the module
  	//! @param pinDIO The number of the digital pin connected to the DIO pin of the module
	//!
	Display(uint8_t pinClk, uint8_t pinDIO){
		_display = new TM1637Display(pinClk, pinDIO);
		_display->setBrightness(1);
		_display->clear();

		_ms = 0;
		_msOld = 0;
		_msSum = 0;
		_blink = false;
	}

	//! Show time value on this display.
	//! @param time The time object displayed on this display.
	//!
	void ShowTime(Time time){
		_display->showNumberDec(time.GetMinute(), true, 2, 2);
		_display->showNumberDecEx(time.GetHour(), 0b01000000, true, 2, 0);	
	}
};

#endif