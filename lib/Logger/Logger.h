/*
  Logger.h - Static library for logging messages via Serial comm.
*/
#ifndef Logger_h
#define Logger_h

#include "Arduino.h"
#include "ILoggable.h"
#include "RTC.h"

#define SEPARATOR ';'

class Logger{
private:
    
public:
    //! Start serial communication.
    //! @param baud Baudrate.
    //!
    static void Setup(unsigned long baud = 9600){
	    Serial.begin(baud);
        while (!Serial) {
            ; // wait for serial port to connect. Needed for native USB port only
        }
    }

    static void Log_(RTC* rtc, ILoggable* object, char msg1[50]){
        String timeStr = (rtc == NULL) ? "null time" : rtc->GetTimeStr();
        String objectStr = (object == NULL) ? "null object" : object->GetLogName();
        Serial.print(timeStr);
        Serial.print(SEPARATOR); 
        Serial.print(objectStr);
        Serial.print(SEPARATOR);  
        Serial.print(msg1); 
        Serial.println();
    }

    static String LogStr_(RTC* rtc, ILoggable* object, String msg1){
        String timeStr = (rtc == NULL) ? "null time" : rtc->GetTimeStr();
        String objectStr = (object == NULL) ? "null object" : object->GetLogName();
        // Serial.print(timeStr);
        // Serial.print(SEPARATOR);
        // Serial.print(objectStr);
        // Serial.print(SEPARATOR); 
        // Serial.print(msg1); 
        Serial.println(timeStr + String(SEPARATOR) + objectStr + String(SEPARATOR) + msg1);
        return timeStr + String(SEPARATOR) + objectStr + String(SEPARATOR) + msg1;
    }

    static void Log_(ILoggable* object, char msg1[50]){
        Log_(NULL, object, msg1);
    }

    static void Log_(char msg1[50]){
        Log_(NULL, NULL, msg1);
    }
};
#endif