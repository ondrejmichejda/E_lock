/*
  Key.h - Library for handle key of keyboard.
*/
#ifndef Key_h
#define Key_h

#define LONGPRESS 3000

#include "Arduino.h"
#include "TOn.h"

class Key
{
private:
	int _pin;
	String _name;
	TOn _ton;
	bool _click;
	bool _clickOld;
	bool _long;
	bool _longOld;

public:
	Key(int p, String name):_ton(LONGPRESS){
		_pin = p;
		_name = name;
		pinMode(_pin, INPUT_PULLUP);

		_click = false;
		_clickOld = false;
		_long = false;
		_longOld = false;
		Click = false;
		Long = false;
	}

	void Monitor(){
		_click = digitalRead(_pin) == LOW;

		// setup ton input
		_ton.In = _click;
		_long = _ton.Out;	

		// reset public flags
		Long = false;
		Click = false;	

		// long pressed first priority
		if(_long && !_longOld){
			Long = true;
			Serial.println("Key " + _name + " long");
		}
		// click if no ton.out active in this cycle (to prevent click flag on release of long hold)
		else if (!_click && _clickOld && !_ton.Out){
			Click = true;
			Serial.println("Key " + _name + " click");
		}
		_longOld = _long;
		_clickOld = _click;	

		// ton run code itself (must be after click condition)
		_ton.Run();								
	}

	bool Click;
	bool Long;
};

#endif