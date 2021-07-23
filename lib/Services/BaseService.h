/*
  BaseService.h - Base abstract class for services.
*/

#include "Logger.h"

#ifndef BaseService_h
#define BaseService_h

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
	
    String initText = "Initialized";
    String failText = "Failed";

	//! Initialization of all obects, call after fail.
	virtual void _init() = 0;

	//! Do the work.	
	virtual void _work() = 0;

	//! Failed. What to do when service fails.
	virtual void _failed() = 0;

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