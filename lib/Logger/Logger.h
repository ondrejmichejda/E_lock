/*
  Logger.h - Static library for logging messages via Serial comm.
*/
#ifndef Logger_h
#define Logger_h

#include "Arduino.h"
#include "ILoggable.h"
#include "Time.h"

class Logger{
public:
    //! Start serial communication.
    //! @param baud Baudrate.
    //!
    static void Setup(unsigned long baud = 9600){
	    Serial.begin(baud);
    }

    static void Log(Time* time, ILoggable* object, String msg){
        Serial.println(time->GetTimeStr() + " - " +
        String(object->GetLogName()) + " : " + 
        msg);
    }

};

#endif