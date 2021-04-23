/*
  ICardReader.h - Interface for card reader objects.
*/
#ifndef ICardReader_h
#define ICardReader_h

#include "Arduino.h"

class ICardReader
{
public:
    // Method of main cyclic function
	virtual void Run() = 0;

    // Return true if new data
    virtual bool NewData() = 0;

    // Return data
    virtual String GetData() = 0;

    // Clear buffer and enable reading
    virtual void ClearBuffer() = 0;
};

#endif