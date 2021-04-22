/*
  Time.h - Library for handle time.
*/
#ifndef Time_h
#define Time_h

#define MAX_TIME 1439

#include "ITime.h"

class Time : public ITime
{
private:
	// 1 / ticks per minute
	double _multiplier;

	int _time;
	int _tickCtr;
	int _minOld;
	bool _pause;

	//! Calculate total minutes from ticks.
	//! @param ticks Number of ticks.
	//! @return Minutes.
	//!
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
	//! Initializes Time object
	//! @param startTime Total minute as initial time.
	//! @param multiplier 1/Ticks per minute used when Tick() is called.
	//!
	Time(long startTime, double multiplier){
		_multiplier = (multiplier <= 0) ? 1 : multiplier;
		_tickCtr = startTime * _multiplier;
		_minOld = 0;
		_pause = false;
	}

	//! Initializes Time object
	//! @param hour Initial hours.
	//! @param minute Initial minutes.
	//! @param multiplier 1/Ticks per minute used when Tick() is called.
	//!
	Time(int hour, int minute, double multiplier) : Time(hour * 60 + minute, multiplier){}

	//! Call to change minute value. Calculating with multiplier.
	void Tick(){
		_tickCtr++;
		_overflowCheck();
		_time = _timeCalc(_tickCtr);
	}

	//! Checks whether total value has been changed.
	//! @return TRUE if time has changed.
	//!
	bool Changed(){
		int totalMin = GetTimeInt();
		if(_minOld != totalMin){
			_minOld = totalMin;
			return true;
		}
		return false;	
	}

	//! Get actual hours.
	//! @return Hours.
	//!
	int GetHour(){
		_time = _timeCalc(_tickCtr);
		return _time / 60;
	}

	//! Get actual minutes.
	//! @return Minutes.
	int GetMinute(){
		_time = _timeCalc(_tickCtr);
		return _time % 60;
	}

	//! Get total minutes.
	//! @return Total minutes.
	int GetTimeInt(){
		_time = _timeCalc(_tickCtr);
		return _time;
	}

	//! Get time in string format HH:mm
	//! @return Time as HH:mm
	//!
	String GetTimeStr(){
        String hour = (GetHour() < 10) ? "0" + String(GetHour()) : String(GetHour());
        String min = (GetMinute() < 10) ? "0" + String(GetMinute()) : String(GetMinute());
		return hour + ":" + min;
	}

	//! Modify time by 1 for desired scale (hour, minute).
	//! @param hour TRUE to change hour, FALSE to change minutes.
	//! @param dir TRUE to increase, FALSE to decrease.
	//!
	void Modify(bool hour, bool dir){
		
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