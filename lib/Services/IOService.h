#ifndef IOService_h
#define IOService_h

#include "Arduino.h"
#include "BaseService.h"
#include "TimeService.h"
#include "Logger.h"
#include "Key.h"
#include "Display.h"
#include "CardReader125.h"
#include "RGBLED.h"
#include "Relay.h"

//! Class covering all IO periferies and it's functionalities.
class IOService : public BaseService, public ILoggable
{
private:
    TimeService* _timeService = NULL;

    //! Initialization.
    void _init(){
        LockRelay = new Relay(1);
        Display1 = new Display(2, 3);
        Reader = new CardReader125(8);
        Led = new RGBLED(9, 10, 11);
        
        Logger::Log(_timeService->TimeAct, this, initText);
    }

    //! Work to be done.
    void _work(){
        Reader->Run();
        Led->Run();
        
        if(LockRelay->Opened()){
            char openedTxt[] = "LockRelay opened (Locked)";
            Logger::Log(_timeService->TimeAct, this, openedTxt);
        }
            

        if(LockRelay->Closed()){
            char closedTxt[] = "LockRelay closed (Unlocked)";
            Logger::Log(_timeService->TimeAct, this, closedTxt);
        }

        LockRelay->Run();

        if(_timeService->TimeAct->Changed())
            Display1->ShowTime(_timeService->TimeAct);
    }

    //! Failed.
    void _failed(){
        Logger::Log(_timeService->TimeAct, this, failText);
    }

public:
    //! Display definition
    Display* Display1;

    // Card reader
    CardReader125* Reader;

    //RGB LED
    RGBLED* Led;

    //Relay for lock control
    Relay* LockRelay;

    Key* Key1;
    Key* Key2;
    Key* Key3;
    Key* Key4;

    //! Initializes IOService.
    //! @param timeService Reference to TimeService.
    //!
    IOService(TimeService* timeService){
        _timeService = timeService;
        Display1 = NULL;
        Reader = NULL;
        Led = NULL;

        _init();
    }

    String GetLogName(){
        return "IO Service";
    }
};

#endif