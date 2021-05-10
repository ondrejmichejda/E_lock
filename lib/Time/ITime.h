/*
  ITime.h - Interface for time objects.
*/
#ifndef ITime_h
#define ITime_h

#include "Arduino.h"

class ITime
{
public:
	//! Checks whether total value has been changed.
	//! @return TRUE if time has changed.
	//!
	virtual bool Changed() = 0;

	//! Get actual hours.
	//! @return Hours.
	//!
	virtual int GetHour() = 0;

	//! Get actual minutes.
	//! @return Minutes.
	virtual int GetMinute() = 0;

    //! Get actual seconds.
    //! @return Seconds.
    virtual int GetSecond() = 0;

	//! Get total minutes.
	//! @return Total minutes.
	virtual int GetTimeInt() = 0;

	//! Get time in string format HH:mm
	//! @return Time as HH:mm
	//!
	virtual String GetTimeStr() = 0;

    //! Set the time
    //! @param h Hours to set
    //! @param m Minutes to set
    //! @param s Seconds to set
    virtual void SetTime(uint8_t h, uint8_t m = 0, uint8_t s = 0) = 0;
};

#endif