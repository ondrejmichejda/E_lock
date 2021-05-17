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

#define USER_COUNT 2

class AuthService : public BaseService, public ILoggable
{
private:
    IOService* _ioService;
    TimeService* _timeService;
    String _users[USER_COUNT];

    //! Initialization.
    void _init(){
        Logger::Log(_timeService->TimeAct, this, initText);
    }

    //! Work to be done.
    void _work(){
        if(_ioService->Reader->NewData()) {
            String code = _ioService->Reader->GetData();
            if(_verifyUser(code)){
                Logger::LogStr(_timeService->TimeAct, this, "OK("+code+")");
                _ioService->Led->Green();
            }
            else {
                Logger::LogStr(_timeService->TimeAct, this, "Failed("+code+")");
                _ioService->Led->Red();
            }
        }
    }

    //! Failed.
    void _failed(){
        Logger::Log(_timeService->TimeAct, this, failText);
    }

    bool _verifyUser(String code){
        bool result = false;
        for (size_t i = 0; i < USER_COUNT; i++){
            if(code.equals(_users[i])){
                result = true;
                break;
            }
        }
        return result;
    }

public:
    AuthService(TimeService* timeService, IOService* ioService){
        _timeService = timeService;
        _ioService = ioService;

        //Set authenticated users into array _users
        _users[0] = "5448487069656868486653";
    }

    String GetLogName(){
        return Name;
    }
};

#endif