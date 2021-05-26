/*
    Serial Service - Communication via com port with pc and handles commands.
*/

#ifndef SerialService_h
#define SerialService_h

#include "IOService.h"

#define COMMPWD 139

class SerialService : public BaseService, public ILoggable
{
private:
    TimeService* _timeService;
    IOService* _ioService;

    // Command definition
    enum Command{
        UNDEFINED = 0,
        SETTIME = 1,
        UNLOCK = 2,
        LEDTEST = 3,
        GETLOG = 9
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
            uint8_t pwd = _splitString(message, ';', 0).toInt();

            if(!_handshake(pwd)){
                // Wrong password for communication from PC
                Logger::LogStr(_timeService->TimeAct, this, "Invalid handshake. Aborted");
            }
            else{
                Command cmd = _getEnumFromCmd(_splitString(message, ';', 1));

                if(cmd == UNDEFINED){
                    // Invalid command
                    Logger::LogStr(_timeService->TimeAct, this, "Invalid cmd: '" + String(cmd) + "'");
                }
                else{
                    // All checks passed, trying to process command
                    String args = _splitString(message, ';', 2);
                    Logger::LogStr(_timeService->TimeAct, this, "New valid cmd: '" + String(cmd) + "'");
                    Logger::LogStr(_timeService->TimeAct, this, "Args: '" + args + "'");
                    _tryProcessCommand(cmd, args);
                    
                }
            }
        }
    }

    //! Failed.
    void _failed(){
        Logger::Log(_timeService->TimeAct, this, failText);
    }

    //! String split function
    //! @param data Input string to be splitted
    //! @param separator Split separator char
    //! @param index Index of element after split to be returned
    //! @return Requested part of input string as string
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

    //! Verify communication with PC partner
    //! @param in Received handshake code
    //! @return True if handshake code check succesful
    bool _handshake(uint8_t in){
        return COMMPWD == in;
    }

    //! Get command enum from string value
    //! @param cmd Command in string format
    //! @return Command enum value
    Command _getEnumFromCmd(String cmd){
        Command result = UNDEFINED;
        switch (cmd.toInt())
        {
        case 1:
            result = SETTIME;
            break;
        case 2:
            result = UNLOCK;
            break;
        case 3:
            result = LEDTEST;
            break;
        case 9:
            result = GETLOG;
            break;
        default:
            result = UNDEFINED;
            break;
        }
        return result;
    }

    //! Processing command with arguments
    //! @param cmd Command enum to process
    //! @param args String arugments
    void _tryProcessCommand(Command cmd, String args){
        switch (cmd){
            case SETTIME:
                // 1;10:43:15:5:12:2020
                _setDateTime(args);
                break;
            case UNLOCK:
                _ioService->Unlock();
                break;
            case LEDTEST:
                // arguments for LED test: r = red, g = green, b = blue
                if(args == "r")
                    _ioService->Led->Red();
                else if(args == "g")
                    _ioService->Led->Green();
                else if(args == "b")
                    _ioService->Led->Blue();
                break;
            default:
                break;
        }
    }

    //! Set date and time to RTC
    //! @param arg Date and time value in format hh:mm:ss:dd:MM:yy
    void _setDateTime(String arg){
        uint8_t h = _splitString(arg, ':', 0).toInt();
        uint8_t m = _splitString(arg, ':', 1).toInt();
        uint8_t s = _splitString(arg, ':', 2).toInt();
        uint8_t d = _splitString(arg, ':', 3).toInt();
        uint8_t MM = _splitString(arg, ':', 4).toInt();
        uint16_t y = _splitString(arg, ':', 5).toInt();

        if(y < 2021){
            Logger::LogStr(_timeService->TimeAct, this, "Invalid year. Aborted");
            return;
        }

        _timeService->TimeAct->SetTime(h, m, s, d, MM, y);
        Logger::LogStr(_timeService->TimeAct, this, "Time set");
    }

public:
    SerialService(TimeService* timeService, IOService* ioService){
        _timeService = timeService;
        _ioService = ioService;
        _init();
    }

    String GetLogName(){
        return "Serial Service";
    }
};

#endif