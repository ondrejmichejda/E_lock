#ifndef BaseService_h
#define BaseService_h

#include "Arduino.h"

class BaseService 
{
private:
	//! Status check function. If status bad, then restart service.
	void _statusCheck(){
		if(!_status){
			_log("Service Failed");
			_init();
		}
	}

protected:
	//! Service status. True if ok.
	bool _status;

	//! Initialization of all obects, call after fail.
	virtual void _init();

	//! Do the work.	
	virtual void _work();

	//! Log message to serial port.
	//! @param log Message to be logged.
	//!
	void _log(String log){
		Serial.println("Service '" + String(Name) + "' -> " + String(log));
	}

public:

	//! Name of service.
	char Name[20];

	//! Main task run in loop.
	void Run(){
		_work();
		_statusCheck();
	}

	//! Fake constructor used in SETUP function in main.cpp.
	//! @param name Name of this service.
	//!
	void Setup(String name){
		name.toCharArray(Name, 20);
		_init();
	}

};

#endif