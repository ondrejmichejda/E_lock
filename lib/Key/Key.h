/*
  Key.h - Library for handle key of keyboard.
*/
#ifndef Key_h
#define Key_h

#define LONGPRESS 2000

#include "Arduino.h"
#include "TimeService.h"
#include "TOn.h"
#include "ILoggable.h"
#include "Logger.h"

//! Class to cover button functionality.
class Key : public ILoggable
{
private:
	int _pin;
	TOn* _ton = NULL;
    TimeService* _timeService = NULL;
	bool _click;
	bool _clickOld;
	bool _long;
	bool _longOld;

public:
	// Button clicked (on release)
	bool Click;

	// Button hold more then LONGPRESS = 3000
	bool Long;

    // Button name
    String Name;

	//! Initializes button object.
	//! @param pin Used pin for this button.
	//! @param name Name of this button.(it's numeric value)
	//!
	Key(int pin, String name, TimeService* timeService){
        _timeService = timeService;
		_pin = pin;
		Name = String(name);
		pinMode(_pin, INPUT_PULLUP);

		// init variables
		Click = false;
		Long = false;

		_ton = new TOn(LONGPRESS);
		_click = false;
		_clickOld = false;
		_long = false;
		_longOld = false;
	}

	//! Monitoring function to catch up button presses.
	void Run(){
		_click = digitalRead(_pin) == LOW;

		// setup ton input
		_ton->In = _click;
		_long = _ton->Out;	

		// reset public flags
		Long = false;
		Click = false;	

		// long pressed first priority
		if(_long && !_longOld){
			Long = true;
			Logger::Log(_timeService->TimeAct, this, Name, Texts::Hold);
		}
		// click if no ton.out active in this cycle (to prevent click flag on release of long hold)
		else if (!_click && _clickOld && !_ton->Out){
			Click = true;
			Logger::Log(_timeService->TimeAct, this, Name, Texts::Click);
		}
		_longOld = _long;
		_clickOld = _click;	

		// ton run code itself (must be after click condition)
		_ton->Run();								
	}

    String GetLogName(){
        return "Button";
    }
};

#endif