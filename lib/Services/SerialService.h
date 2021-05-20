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
            String message = Serial.readString();
            Command cmd = _getEnumFromCmd(_splitString(message, ';', 0));
            String args = _splitString(message, ';', 1);
            if(cmd != UNDEFINED){
                Logger::LogStr(_timeService->TimeAct, this, "New valid cmd: '" + String(cmd) + "'");
                Logger::LogStr(_timeService->TimeAct, this, "Args: '" + args + "'");
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

    String _splitString(String data, char separator, int index){
        int found = 0;
        int strIndex[] = {0, -1};
        int maxIndex = data.length()-1;

        for(int i=0; i<=maxIndex && found<=index; i++){
            if(data.charAt(i)==separator || i==maxIndex){
                found++;
                strIndex[0] = strIndex[1]+1;
                strIndex[1] = (i == maxIndex) ? i+1 : i;
            }
    }

    return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
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