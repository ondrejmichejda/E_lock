/*
  ILoggable.h - Interface used for loggable objects.
*/

#ifndef ILoggable_h
#define ILoggable_h

#include "Arduino.h"

class ILoggable{
public:
    // Must be overriden in child class.
    virtual String GetLogName();
};

#endif