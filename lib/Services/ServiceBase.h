#ifndef ServiceBase_h
#define ServiceBase_h

#include "Arduino.h"

class ServiceBase 
{
private:
	void StatusCheck(){
		if(!Status){
			Log("Service Failed");
			Init();
		}
	}

protected:
	// Service status. True if ok.
	bool Status;

	// Initialization of all obects, call after fail.
	virtual void Init();

	// Do the work.	
	virtual void Work();

	// Log message to serial port.
	void Log(String log){
		Serial.println("Service '" + String(Name) + "' -> " + String(log));
	}

public:
	// Name of service.
	char Name[20];
	// Main task run in loop.
	void Run(){
		Work();
		StatusCheck();
	}

	// Fake constructor.
	void Setup(String n){
		n.toCharArray(Name, 20);
		Init();
	}
};

#endif