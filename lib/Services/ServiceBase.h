#ifndef ServiceBase_h
#define ServiceBase_h

#include "Arduino.h"

class ServiceBase
{
private:
	void StatusCheck(){
		if(!Status){
			Serial.println("disposed serivice");
			Init();
		}
	}

protected:
	// Service status. True if ok.
	bool Status;
	virtual void Init();
	virtual void Work();

public:
	void Run(){
		Work();
		StatusCheck();
	}

};

#endif