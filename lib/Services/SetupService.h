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
    int8_t _hour = 0;                               // hour in edit mode
    int8_t _min = 0;                                // minute in edit mode
    int _minOld = 0;                        

    // Initialization.
    void _init(){
        // init code here
        Logger::Log(_timeService->TimeAct, this, initText);
    }

    // Work to be done.
    void _work(){

        //***** ENTER TIME EDIT MODE *****
        // 1. Hold button 1 to enter password mode
        // 2. Enter password combination 1-4-2-3 to enter edit mode 
        // (If not entered till 10s -> exit password mode)
        // 3. Edit time: hour 1/2 minute 3/4 buttons
        // 4. Hold button 1 to exit edit mode
        //********************************

        // If mode 0 display time
        if(_mode == 0 && _timeService->TimeAct->Changed()){
            _ioService->Display1->ShowTime(_timeService->TimeAct);
        }
        else if(_mode == 2 && _minChanged()){
            _ioService->Display1->ShowTime(_hour, _min);
        }

        // 1. Hold button 1 to enter password mode
        if(_ioService->Key1->Long && _mode == 0){
            _mode = 1;
        }

        // Exit password mode after 10s
        if(_mode == 1 && _pwdModeTimeout->Out){
            _pwdModeTimeout->In = false;
            _mode = 0;
            char pwdTimeoutText[] = "Exit Password mode (timeout)";
            Logger::Log(_timeService->TimeAct, this, pwdTimeoutText);
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
            if(_ioService->Key1->Click)
                _hour++;
            if(_ioService->Key2->Click)
                _hour--;
            if(_ioService->Key3->Click)
                _min++;
            if(_ioService->Key4->Click)
                _min--;

            if(_ioService->Key3->Long)
                _min = _min + 10;
            if(_ioService->Key4->Long)
                _min = _min - 10;
            
            if(_ioService->Key1->Click || _ioService->Key2->Click || _ioService->Key3->Click || _ioService->Key4->Click)
                _editModeTimeout->Elapsed = 0;
        }

        // Exit edit mode after 20s of inactivity or 
        // 4. Hold button 1 to exit edit mode
        if(_mode == 2 && (_editModeTimeout->Out || _ioService->Key1->Long)){
            _editModeTimeout->In = false;
            _mode = 0;
            _timeService->TimeAct->SetTime(_hour, _min);
            _ioService->Display1->TurnOff();
            delay(1000);
            char exitEditText[] = "Exit Edit mode - Time changed";
            Logger::Log(_timeService->TimeAct, this, exitEditText);
        }

        // ***************************
        // Transitions of mode

        // Entering normal mode
        if(_mode == 0 && _modeOld != 0){
            char enterNormalText[] = "Enter normal mode";
            Logger::Log(_timeService->TimeAct, this, enterNormalText);
            _insPwd[0] = 0;
            _insPwd[1] = 0;
            _insPwd[2] = 0;
            _insPwd[3] = 0;
            _pwdModeTimeout->ReInit();
            _editModeTimeout->ReInit();
        }

        // Entering password mode
        if(_mode == 1 && _modeOld != 1){
            char enterPwdText[] = "Enter Password mode";
            Logger::Log(_timeService->TimeAct, this, enterPwdText);
            _ioService->Display1->ShowPwdMode();
            _pwdModeTimeout->In = true;
        }

        // Entering Edit mode
        if(_mode == 2 && _modeOld != 2){
            _hour = _timeService->TimeAct->GetHour();
            _min = _timeService->TimeAct->GetMinute();
            _pwdModeTimeout->In = false;
            _ioService->Display1->ShowTime(_hour, _min);
            _editModeTimeout->In = true;
            char enterEditText[] = "Enter Edit mode";
            Logger::Log(_timeService->TimeAct, this, enterEditText);
        }

        _modeOld = _mode;

        _pwdModeTimeout->Run();
        _editModeTimeout->Run();
        
        // Edit hour and minute overflow check
        if(_hour > 23) _hour = 0;
        if(_min > 59) _min = 0;

        if(_hour < 0) _hour = 23;
        if(_min < 0) _min = 59;
    }

    // Failed.
    void _failed(){
        Logger::Log(_timeService->TimeAct, this, failText);
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

    //! Checks whether edit time changed.
    //! @return True if edit time changed.
    bool _minChanged(){
        int totalMin = _hour * 60 + _min;
		if(_minOld != totalMin){
			_minOld = totalMin;
			return true;
		}
		return false;	
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

        _init();
    }

    String GetLogName(){
        return "Setup Service";
    }
};

#endif