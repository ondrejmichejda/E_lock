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

    static void Log(Time* time, ILoggable* object, String msg1, String msg2 = "", String msg3 = "", String msg4 = "", String msg5 = ""){
        String timeStr = (time == NULL) ? "null" : time->GetTimeStr();

        String objectStr = (object == NULL) ? "null" : object->GetLogName();

        Serial.println(timeStr + " - " + objectStr + " : " + msg1 + " " + msg2 + " " + msg3 + " " + msg4 + " " + msg5);
    }

    static void Log(ILoggable* object, String msg1, String msg2 = "", String msg3 = "", String msg4 = "", String msg5 = ""){
        Log(NULL, object, msg1, msg2, msg3, msg4, msg5);
    }

    static void Log(String msg1, String msg2 = "", String msg3 = "", String msg4 = "", String msg5 = ""){
        Log(NULL, NULL, msg1, msg2, msg3, msg4, msg5);
    }

};

#endif