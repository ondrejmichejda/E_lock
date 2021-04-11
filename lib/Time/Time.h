/*
  Time.h - Library for handle time.
*/
#ifndef Time_h
#define Time_h

#include "Arduino.h"

class Time
{
private:
	// 1 / ticks per minute
	double _multiplier;
	int _time;
	int _tickCtr;
	int _minOld;
	bool _editMode;
	bool _pwdMode;

	// Calculate total minutes from ticks.
	int _timeCalc(int ticks){
		return floor(_overflowCheck(ticks) / _multiplier);
	}

	// Verify and reset if overflows.
	int _overflowCheck(int ticks){
		int result = 0;
		if(ticks < 1440 * _multiplier){
			result = ticks;
		}
		return result;
	}

public:
	// Constructor to create absolute minute time.
	Time(long startTime, double multiplier){
		_multiplier = (multiplier <= 0) ? 1 : multiplier;
		_tickCtr = startTime * _multiplier;

		_minOld = 0;
		_editMode = false;
		_pwdMode = false;
	}

	// Contructor to create hour and minute time.
	Time(int hour, int minute, double multiplier) : Time(hour * 60 + minute, multiplier){}

	// Call to change minute value.
	void Tick(){
		if(!_editMode){
			_tickCtr++;
			_time = _timeCalc(_tickCtr);
		}
	}

	// Empty constructor
	Time() : Time(0, 1){}

	/* Checks whether minute value has been changed.
	Returns true if changed.*/
	bool Changed(){
		int min = GetMinute();
		if(_minOld != min){
			_minOld = min;
			return true;
		}
		return false;	
	}

	// Get hour value.
	int GetHour(){
		_time = _timeCalc(_tickCtr);
		return _time / 60;
	}

	// Get minute value.
	int GetMinute(){
		_time = _timeCalc(_tickCtr);
		return _time % 60;
	}

	// Get total minutes.
	int GetTotalMin(){
		_time = _timeCalc(_tickCtr);
		return _time;
	}

	// Set or reset edit mode.
	void SetEditMode(bool val){
		_editMode = val;
		if(_editMode)
			SetPwdMode(false);
				
		Serial.println("EditMode = " + String(_editMode));
	}

	// Set or reset password mode.
	void SetPwdMode(bool val){
		_pwdMode = val;
		Serial.println("PwdMode = " + String(_pwdMode));
	}

	// Get edit mode status.
	bool GetEditMode(){
		return _editMode;
	}

	// Get password mode status.
	bool GetPwdMode(){
		return _pwdMode;
	}

	// Modify time by 1 for desired scale (hour, minute).
	void Modify(bool hour, bool dir){
		if(!_editMode) return;
		
		if(hour){
			// modify hour
			int hour = 60 * _multiplier;
			_tickCtr += dir ? hour : -hour;
		}
		else{
			int minute = _multiplier;
			_tickCtr += dir ? minute : -minute;
		}
	}
};

#endif