/*
  BaseService.h - Base abstract class for services.
*/

#ifndef BaseService_h
#define BaseService_h

#include "Arduino.h"
#include "Texts.h"

class BaseService
{
private:
    //! Service status. True if ok.
	bool _status;

	//! Status check function. If status bad, then restart service.
	void _statusCheck(){
		if(!_status){
			_failed();
			_init();
            _status = true;
		}
	}

protected:
	
	//! Initialization of all obects, call after fail.
	virtual void _init();

	//! Do the work.	
	virtual void _work();

	//! Failed. What to do when service fails.
	virtual void _failed();

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

    //! Returns status of this service.
    //! @return Status of this service.
    //!
    bool GetStatus(){
        return _status;
    }

    // Set status bad.
    //
    void SetStatusBad(){
        _status = false;
    }

};

#endif