/*
    AuthService - Authentication service.
*/

#ifndef AuthService_h
#define AuthService_h

#include "Arduino.h"
#include "BaseService.h"
#include "TimeService.h"
#include "IOService.h"
#include "Logger.h"

class AuthService : public BaseService, public ILoggable
{
private:
    IOService* _ioService;
    TimeService* _timeService;

    //! Initialization.
    void _init(){
        Logger::Log(_timeService->TimeAct, this, initText);
    }

    //! Work to be done.
    void _work(){
    }

    //! Failed.
    void _failed(){
        Logger::Log(_timeService->TimeAct, this, failText);
    }

public:
    AuthService(TimeService* timeService, IOService* ioService){
        _timeService = timeService;
        _ioService = ioService;
    }

    String GetLogName(){
        return Name;
    }
};

#endif