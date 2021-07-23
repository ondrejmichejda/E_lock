#ifndef IOService_h
#define IOService_h

#include "TimeService.h"
#include "StorageService.h"
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
    StorageService* _storageService = NULL;

    //! Initialization.
    void _init(){
        LockRelay = new Relay(7);
        Display1 = new Display(2, 3);
        Reader = new CardReader125(10);
        Led = new RGBLED(5, 6, 4);
        
        _storageService->Log(_timeService->TimeAct, this, initText);
    }

    //! Work to be done.
    void _work(){
        Reader->Run();
        Led->Run();
        
        if(LockRelay->Opened()){
            _storageService->Log(_timeService->TimeAct, this, "LockRelay opened (Locked)");
        }
            

        if(LockRelay->Closed()){
            _storageService->Log(_timeService->TimeAct, this, "LockRelay closed (Unlocked)");
        }

        LockRelay->Run();

        if(_timeService->TimeAct->Changed())
            Display1->ShowTime(_timeService->TimeAct);
    }

    //! Failed.
    void _failed(){
        _storageService->Log(_timeService->TimeAct, this, failText);
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
    IOService(StorageService* storageService, TimeService* timeService){
        _timeService = timeService;
        _storageService = storageService;
        Display1 = NULL;
        Reader = NULL;
        Led = NULL;

        _init();
    }

    // Unlock with led signalization
    void Unlock(){
        _storageService->Log(_timeService->TimeAct, this, "Unlocking");
        Led->Green();
        LockRelay->Close();
    }

    String GetLogName(){
        return "IO Service";
    }
};

#endif