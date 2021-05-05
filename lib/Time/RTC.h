/*
  RTC.h - Library for handle Real Time Clock.
*/
#ifndef RTC_h
#define RTC_h

#include "ITime.h"
#include "Wire.h"
#include "RTCLib.h"


class RTC : public ITime
{
private:
    RTC_DS3231* _rtc;
    uint8_t _minOld;
public:
	//! Initializes Time object
	RTC(){
        _rtc = new RTC_DS3231();
        if (! _rtc->begin()) {
            // Serial.println("Couldn't find RTC");
            Serial.flush();
            abort();
        }
        
        if (_rtc->lostPower()) {
            Serial.println("RTC lost power, let's set the time!");
            // When time needs to be set on a new device, or after a power loss, the
            // following line sets the RTC to the date & time this sketch was compiled
            _rtc->adjust(DateTime(F(__DATE__), F(__TIME__)));
            // This line sets the RTC with an explicit date & time, for example to set
            // January 21, 2014 at 3am you would call:
            // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
        }
    }

    //! Returns datetime of actual rtc.
    //! @return Actual datetime.
    DateTime GetDateTime(){
        return _rtc->now();
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
		return _rtc->now().hour();
	}

	//! Get actual minutes.
	//! @return Minutes.
	int GetMinute(){
		return _rtc->now().minute();
	}

    //! Get actual seconds.
	//! @return Seconds.
	int GetSecond(){
		return _rtc->now().second();
	}

	//! Get total minutes.
	//! @return Total minutes.
	int GetTimeInt(){
		return _rtc->now().hour() * 60 + _rtc->now().minute();
	}

	//! Get time in string format HH:mm
	//! @return Time as HH:mm
	//!
	String GetTimeStr(){
        String hour = (GetHour() < 10) ? "0" + String(GetHour()) : String(GetHour());
        String min = (GetMinute() < 10) ? "0" + String(GetMinute()) : String(GetMinute());
        String sec = (GetSecond() < 10) ? "0" + String(GetSecond()) : String(GetSecond());
		return _rtc->now().day() + String(".") + _rtc->now().month() + String(".") + _rtc->now().year() + " " + hour + ":" + min + ":" + sec;
	}

	//! Modify time by 1 for desired scale (hour, minute).
	//! @param dt Datetime to set.
	void Modify(DateTime dt){
		_rtc->adjust(dt);
	}

    void Modify(bool hour, bool dir){
		// do nothing
	}
};

#endif