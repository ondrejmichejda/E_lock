/*
  Logger.h - Static library for logging messages via Serial comm.
*/
#ifndef Logger_h
#define Logger_h

#include "Arduino.h"
#include "ILoggable.h"
#include "RTC.h"

class Logger{
public:
    //! Start serial communication.
    //! @param baud Baudrate.
    //!
    static void Setup(unsigned long baud = 9600){
	    Serial.begin(baud);
    }

    static void Log(RTC* rtc, ILoggable* object, char msg1[50]){
        String timeStr = (rtc == NULL) ? "null" : rtc->GetTimeStr();
        String objectStr = (object == NULL) ? "null" : object->GetLogName();
        String logString = timeStr + " - " + objectStr + " : " + msg1;
        Serial.println(logString);  
    }

    static void Log(RTC* rtc, ILoggable* object, String msg1){
        String timeStr = (rtc == NULL) ? "null" : rtc->GetTimeStr();
        String objectStr = (object == NULL) ? "null" : object->GetLogName();
        String logString = timeStr + " - " + objectStr + " : " + msg1;
        Serial.println(logString); 
    }

    static void Log(ILoggable* object, char msg1[50]){
        Log(NULL, object, msg1);
    }

    static void Log(char msg1[50]){
        Log(NULL, NULL, msg1);
    }
};
#endif