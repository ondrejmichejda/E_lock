/*
  RTCEdit.h - Library for handle Real Time Clock edit value.
*/
#ifndef RTCEdit_h
#define RTCEdit_h

#include "ITime.h"
#include "RTCLib.h"

class RTCEdit : public ITime
{
private:
    DateTime* _rtc;
public:
	//! Initializes Time object
	RTCEdit(DateTime dt){
        _rtc = new DateTime(dt);
    }

    //! Returns datetime.
    //! @return Datetime.
    DateTime GetDateTime(){
        DateTime dt(_rtc->year(), _rtc->month(), _rtc->day(), _rtc->hour(), _rtc->minute(), _rtc->second());
        return dt;
    }

	//! Checks whether total value has been changed.
	//! @return TRUE if time has changed.
	//!
	bool Changed(){
        return false;
	}

	//! Get actual hours.
	//! @return Hours.
	//!
	int GetHour(){
		return _rtc->hour();
	}

	//! Get actual minutes.
	//! @return Minutes.
	int GetMinute(){
		return _rtc->minute();
	}

    //! Get actual seconds.
	//! @return Seconds.
	int GetSecond(){
		return _rtc->second();
	}

	//! Get total minutes.
	//! @return Total minutes.
	int GetTimeInt(){
		return 0;
	}

	//! Get time in string format HH:mm
	//! @return Time as HH:mm
	//!
	String GetTimeStr(){
        String hour = (GetHour() < 10) ? "0" + String(GetHour()) : String(GetHour());
        String min = (GetMinute() < 10) ? "0" + String(GetMinute()) : String(GetMinute());
        String sec = (GetSecond() < 10) ? "0" + String(GetSecond()) : String(GetSecond());
		return hour + ":" + min + ":" + sec;
	}

	//! Modify time by 1 for desired scale (hour, minute).
	//! @param hour TRUE to change hour, FALSE to change minutes.
	//! @param dir TRUE to increase, FALSE to decrease.
	//!
	void Modify(bool hour, bool dir){		
		if(hour){
			if(dir){
                _rtc = new DateTime(_rtc->year(), _rtc->month(), _rtc->day(), _rtc->hour() + 1, _rtc->minute(), _rtc->second());  
            }
            else{
                _rtc = new DateTime(_rtc->year(), _rtc->month(), _rtc->day(), _rtc->hour() - 1, _rtc->minute(), _rtc->second()); 
            }
		}
		else{
            if(dir){
                _rtc = new DateTime(_rtc->year(), _rtc->month(), _rtc->day(), _rtc->hour(), _rtc->minute() + 1, _rtc->second());  
            }
            else{
                _rtc = new DateTime(_rtc->year(), _rtc->month(), _rtc->day(), _rtc->hour(), _rtc->minute() - 1, _rtc->second()); 
            }
		}
	}
};

#endif