/*
  BaseService.h - Base abstract class for services.
*/

#ifndef BaseService_h
#define BaseService_h

#include "Arduino.h"

class BaseService
{
private:
    //! Service status. True if ok.
	bool _status = true;

	//! Status check function. If status bad, then restart service.
	void _statusCheck(){
		if(!_status){
			_failed();
			_init();
            _status = true;
		}
	}

protected:
	
    char initText[12] = "Initialized";
    char failText[7] = "Failed";

	//! Initialization of all obects, call after fail.
	virtual void _init();

	//! Do the work.	
	virtual void _work();

	//! Failed. What to do when service fails.
	virtual void _failed();

public:

	//! Main task run in loop.
	void Run(){
		_work();
		_statusCheck();
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