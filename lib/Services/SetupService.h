#ifndef SetupService_h
#define SetupService_h

#include "TimeService.h"
#include "SerialService.h"

// Class to handle time and other settings.
class SetupService : public BaseService, public ILoggable
{
private:
    TimeService* _timeService = NULL;
    IOService* _ioService = NULL;                 
    SerialService* _serialService = NULL; 

    // Initialization.
    void _init(){
        Logger::Log(_timeService->TimeAct, this, initText);
    }

    // Work to be done.
    void _work(){
        
    }

    // Failed.
    void _failed(){
        Logger::Log(_timeService->TimeAct, this, failText);
    }

public:
    //! Initializes SetupService.
    //! @param timeService Reference to TimeService
    //! @param ioService Reference to IOService
    //!
    SetupService(TimeService* timeService, IOService* ioService, SerialService* serialService){
        _timeService = timeService;
        _ioService = ioService;
        _serialService = serialService;
        _init();
    }

    String GetLogName(){
        return "Setup Service";
    }
};

#endif