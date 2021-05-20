/*
    Serial Service - Communication via com port with pc and handles commands.
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

    enum Command{
        UNDEFINED = 0,
        SETTIME = 1,
        GETLOG = 2
    };
    
    //! Initialization.
    void _init(){
        Logger::Log(_timeService->TimeAct, this, initText);
    }

    //! Work to be done.
    void _work(){
        // Serial object configured in Logger static class
        if(Serial.available()){
            Command cmd = _getEnumFromCmd(Serial.readString());
            if(cmd != UNDEFINED){
                Logger::LogStr(_timeService->TimeAct, this, "New valid cmd: '" + String(cmd) + "'");
                //_tryProcessCommand(msg);

            }
            else{
                Logger::LogStr(_timeService->TimeAct, this, "Invalid cmd: '" + String(cmd) + "'");
            }
            
        }
    }

    //! Failed.
    void _failed(){
        Logger::Log(_timeService->TimeAct, this, failText);
    }

    void _tryProcessCommand(Command cmd){
        
    }

    Command _getEnumFromCmd(String cmd){
        Command result = UNDEFINED;
        switch (cmd.toInt())
        {
        case 1:
            result = SETTIME;
            break;
        case 2:
            result = GETLOG;
        default:
            result = UNDEFINED;
            break;
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
};

#endif