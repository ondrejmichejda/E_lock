/*
  Time.h - Library for handle time.
*/
#ifndef Time_h
#define Time_h

#define MAX_TIME 1439

#include "Arduino.h"

class Time
{
private:
	// 1 / ticks per minute
	double _multiplier;
	int _time;
	int _tickCtr;
	int _minOld;
	bool _pause;

	// Calculate total minutes from ticks.
	int _timeCalc(int ticks){
		return floor(ticks / _multiplier);
	}

	// Verify and reset if overflows.
	void _overflowCheck(){
		if(_tickCtr > (MAX_TIME * _multiplier)){
			_tickCtr = 0;
		}
	}

public:
	// Constructor to create absolute minute time.
	Time(long startTime, double multiplier){
		_multiplier = (multiplier <= 0) ? 1 : multiplier;
		_tickCtr = startTime * _multiplier;
		_minOld = 0;
		_pause = false;
	}

	// Contructor to create hour and minute time.
	Time(int hour, int minute, double multiplier) : Time(hour * 60 + minute, multiplier){}

	// Call to change minute value.
	void Tick(){
		if(!_pause)
			_tickCtr++;
		_overflowCheck();
		_time = _timeCalc(_tickCtr);
	}

	// Pause time.
	void Pause(){
		_pause = true;
	}

	// Re-start time.
	void Play(){
		_pause = false;
	}

	/* Checks whether minute value has been changed.
	Returns true if changed.*/
	bool Changed(){
		int min = GetMinute();
		//Serial.println(min);
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

	// Modify time by 1 for desired scale (hour, minute).
	void Modify(bool hour, bool dir){
		if(!_pause) return;
		
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