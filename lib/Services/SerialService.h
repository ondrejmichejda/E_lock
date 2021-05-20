/*
    Serial Service - Communication via com port with pc.
*/

#ifndef SerialService_h
#define SerialService_h

#include "Arduino.h"
#include "BaseService.h"
#include "TimeService.h"
#include "Logger.h"

#define CMDCOUNT 2


class SerialService : public BaseService, public ILoggable
{
private:
    TimeService* _timeService;
    bool _newMsgFlag;
    String _msg;
    String _availableCmds[CMDCOUNT] = {
        "settime",
        "getlog"
    };
    
    //! Initialization.
    void _init(){
        _newMsgFlag = false;
        Logger::Log(_timeService->TimeAct, this, initText);
    }

    //! Work to be done.
    void _work(){
        // Serial object configured in Logger static class
        if(Serial.available()){
            
            String msg = Serial.readString();
            if(_validateCommand(msg)){
                _msg = msg;
                _newMsgFlag = true;
                Logger::LogStr(_timeService->TimeAct, this, "New valid cmd: '" + msg + "'");
            }
            else{
                Logger::LogStr(_timeService->TimeAct, this, "Invalid cmd: '" + msg + "'");
            }
            
        }
    }

    //! Failed.
    void _failed(){
        Logger::Log(_timeService->TimeAct, this, failText);
    }

    bool _validateCommand(String cmd){
        bool result = false;
        for (size_t i = 0; i < CMDCOUNT; i++)
        {
            if(cmd == _availableCmds[i]){
                result = true;
                break;
            }
        }
        return result;
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