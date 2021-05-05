#ifndef SetupService_h
#define SetupService_h

#include "Arduino.h"
#include "BaseService.h"
#include "TimeService.h"
#include "Logger.h"
#include "IOService.h"
#include "TOn.h"

#define PASSWORD_TIMEOUT 100000
#define EDIT_TIMEOUT 20000
#define PASSWORD_DIGITS 4

// Class to handle time and other settings.
class SetupService : public BaseService, public ILoggable
{
private:
    TimeService* _timeService = NULL;
    IOService* _ioService = NULL;
    int _mode = 0;                                  // 0 = run; 1 = password; 2 = edit
    int _modeOld = 0;
    TOn* _pwdModeTimeout = NULL;
    TOn* _editModeTimeout = NULL;
    int _insPwd[PASSWORD_DIGITS] = {0, 0, 0, 0};    // inserted password by user
    int _pwd[PASSWORD_DIGITS] = {1, 4, 2, 3};       // real password to compare with

    // Initialization.
    void _init(){
        // init code here
        Logger::Log(_timeService->TimeAct, this, Texts::Init);
    }

    // Work to be done.
    void _work(){

        //***** ENTER TIME EDIT MODE *****
        // 1. Hold button 1 to enter password mode
        // 2. Enter password combination 1-4-2-3 to enter edit mode 
        // (If not entered till 10s -> exit password mode)
        // 3. Edit time: hour 1/2 minute 3/4 buttons
        // 4. Hold button 4 to exit edit mode
        //********************************

        // If mode 0 display time
        if(_mode == 0 && _timeService->TimeAct->Changed()){
            _ioService->Display1->ShowTime(_timeService->TimeAct);
        }
        // else if(_mode == 2 && _timeService->TimeEdit->Changed()){
        //     _ioService->Display1->ShowTime(_timeService->TimeEdit);
        // }

        // 1. Hold button 1 to enter password mode
        if(_ioService->Key1->Long && _mode == 0){
            _mode = 1;
        }

        // Exit password mode after 10s
        if(_mode == 1 && _pwdModeTimeout->Out){
            _pwdModeTimeout->In = false;
            _mode = 0;
            Logger::Log(_timeService->TimeAct, this, "Exit Password mode (timeout)");
        }

        // 2. Enter password combination 1-4-2-3 to enter edit mode
        if(_mode == 1){
            if(_ioService->Key1->Click)
                _shiftArray(_insPwd, PASSWORD_DIGITS, 1);
            if(_ioService->Key2->Click)
                _shiftArray(_insPwd, PASSWORD_DIGITS, 2);
            if(_ioService->Key3->Click)
                _shiftArray(_insPwd, PASSWORD_DIGITS, 3);
            if(_ioService->Key4->Click)
                _shiftArray(_insPwd, PASSWORD_DIGITS, 4);

            if(_checkPwd(_insPwd, _pwd, PASSWORD_DIGITS))
                _mode = 2;
        }

        // 3. Edit time: hour=1/2 minute=3/4 buttons
        if(_mode == 2){
            // if(_ioService->Key1->Click)
            //     _timeService->TimeEdit->Modify(true, true);
            // if(_ioService->Key2->Click)
            //     _timeService->TimeEdit->Modify(true, false);
            // if(_ioService->Key3->Click)
            //     _timeService->TimeEdit->Modify(false, true);
            // if(_ioService->Key4->Click)
            //     _timeService->TimeEdit->Modify(false, false);
            
            // if(_ioService->Key1->Click || _ioService->Key2->Click || _ioService->Key3->Click || _ioService->Key4->Click)
            //     _editModeTimeout->Elapsed = 0;
        }

        // Exit edit mode after 20s of inactivity or 
        // 4. Hold button 4 to exit edit mode
        if(_mode == 2 && (_editModeTimeout->Out || _ioService->Key4->Long)){
            _editModeTimeout->In = false;
            _mode = 0;
            //_timeService->SetTimeAct();
            Logger::Log(_timeService->TimeAct, this, "Exit Edit mode");
            _ioService->Display1->TurnOff();
            delay(1000);
        }

        // ***************************
        // Transitions of mode

        // Entering normal mode
        if(_mode == 0 && _modeOld != 0){
            Logger::Log(_timeService->TimeAct, this, "Enter normal mode");
            _insPwd[0] = 0;
            _insPwd[1] = 0;
            _insPwd[2] = 0;
            _insPwd[3] = 0;
            _pwdModeTimeout->ReInit();
            _editModeTimeout->ReInit();
        }

        // Entering password mode
        if(_mode == 1 && _modeOld != 1){
            Logger::Log(_timeService->TimeAct, this, "Enter Password mode");
            _ioService->Display1->ShowPwdMode();
            _pwdModeTimeout->In = true;
        }

        // Entering Edit mode
        if(_mode == 2 && _modeOld != 2){
            Logger::Log(_timeService->TimeAct, this, "Enter Edit mode");
            _pwdModeTimeout->In = false;
            //_timeService->SetTimeEdit();
            //_ioService->Display1->ShowTime(_timeService->TimeEdit);
            _editModeTimeout->In = true;
        }

        _modeOld = _mode;

        _pwdModeTimeout->Run();
        _editModeTimeout->Run();
        
    }

    // Failed.
    void _failed(){
        Logger::Log(_timeService->TimeAct, this, Texts::Fail);
    }

    //! Shifts array to left and add newElement to the most right position.
    //! @param arr Reference to password array
    //! @param size Size of password array.
    //! @param newElement New value to be added to the right position
    //!
    void _shiftArray(int* arr, size_t size, int newElement){
        for (size_t i = 0; i < size; i++){
            if (i < size -1)
                arr[i] = arr[i + 1];
            else
                arr[i] = newElement;
        }
    }

    //! Compares inserted password with stored password.
    //! @param insertPwd User inserted password.
    //! @param pwd Internally stored password.
    //! @param size Size of password arrays.
    //!
    bool _checkPwd(int* insertPwd, int* pwd, size_t size){
        bool result = true;
        for (size_t i = 0; i < size; i++){
            if(pwd[i] != insertPwd[i])
                result = false;
        }
        return result;
    }

public:
    //! Initializes SetupService.
    //! @param timeService Reference to TimeService
    //! @param ioService Reference to IOService
    //!
    SetupService(TimeService* timeService, IOService* ioService){
        _timeService = timeService;
        _ioService = ioService;

        _pwdModeTimeout = new TOn(PASSWORD_TIMEOUT);
        _editModeTimeout = new TOn(EDIT_TIMEOUT);
    }

    String GetLogName(){
        return Name;
    }
};

#endif