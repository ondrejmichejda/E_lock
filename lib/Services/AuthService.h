/*
    AuthService - Authentication service.
*/

#ifndef AuthService_h
#define AuthService_h

#include "Arduino.h"
#include "IOService.h"
#include "StorageService.h"
#include "TOn.h"

#define USER_COUNT 2

class AuthService : public BaseService, public ILoggable
{
private:
    IOService* _ioService;
    TimeService* _timeService;
    StorageService* _storageService;
    String _users[USER_COUNT];
    bool _addUserMode_old;
    TOn* _addUserTimer;

    //! Initialization.
    void _init(){
        Logger::Log(_timeService->TimeAct, this, initText);
    }

    //! Work to be done.
    void _work(){
        if(_ioService->Reader->NewData()) {
            String code = _ioService->Reader->GetData();

            if(AddUserMode){
                if(_storageService->AddUser(code)){
                    Logger::LogStr(_timeService->TimeAct, this, "New user added: " + code);
                    AddUserMode = false;
                }
            }
            else{
                if(_verifyUser(code)){
                    Logger::LogStr(_timeService->TimeAct, this, "OK > " + code);
                    _ioService->Unlock();
                }
                else {
                    Logger::LogStr(_timeService->TimeAct, this, "Failed " + code);
                    _ioService->Led->Red();
                }
            }
            
        }

        if(AddUserMode && !_addUserMode_old){
            Logger::LogStr(_timeService->TimeAct, this, "Ready to add new user");
            _addUserTimer->In = true;
        }

        if(_addUserTimer->Out && AddUserMode){
            AddUserMode = false;
            Logger::LogStr(_timeService->TimeAct, this, "Time for adding user passed.");
        }
        _addUserMode_old = AddUserMode;
        _addUserTimer->Run();
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
    bool AddUserMode;

    AuthService(TimeService* timeService, IOService* ioService, StorageService* storageService){
        _timeService = timeService;
        _ioService = ioService;
        _storageService = storageService;

        _addUserTimer = new TOn(10000);

        AddUserMode = false;

        //Set authenticated users into array _users
        //_users[0] = "5448487069656868486653";

        _init();
    }

    String GetLogName(){
        return "Auth Service";
    }
};

#endif