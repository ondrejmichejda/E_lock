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
    bool _newMsgFlag;
    String _msg;
    
    //! Initialization.
    void _init(){
        _newMsgFlag = false;
        Logger::Log(_timeService->TimeAct, this, initText);
    }

    //! Work to be done.
    void _work(){
        // Serial object configured in Logger static class
        if(Serial.available()){
            _newMsgFlag = true;
            _msg = Serial.readString();
        }
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

    bool NewData(){
        return _newMsgFlag;
    }

    String GetData(){
        _newMsgFlag = false;
        String result = _msg;
        _msg = "";
        return result;
    }
};

#endif