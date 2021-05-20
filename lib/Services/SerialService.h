/*
    Serial Service - Communication via com port with pc.
*/

#ifndef SerialService_h
#define SerialService_h

#include "Arduino.h"
#include "BaseService.h"
#include "TimeService.h"
#include "Logger.h"


class SerialService : public BaseService, public ILoggable
{
private:
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
    SerialService(TimeService* timeService){
        _timeService = timeService;

        _init();
    }

    String GetLogName(){
        return "Serial Service";
    }
};

#endif