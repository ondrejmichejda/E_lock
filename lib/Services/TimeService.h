#ifndef TimeService_h
#define TimeService_h

#include "Arduino.h"
#include "BaseService.h"
#include "Time.h"
#include "PulseGenerator.h"
#include "IOService.h"

#define FREQ 600

//! Class covering Time services.
class TimeService : public BaseService
{
private:
    PulseGenerator* Generator = NULL;

    //! Initialization.
    void _init(){
        Generator = new PulseGenerator(FREQ);
        TimeAct = new Time(12, 23, 1);

        _status = true;
        _log("Initialized");
    }

    //! Work to be done.
    void _work(){
        if(Generator->On()){
            TimeAct->Tick();
        }
    }

public:
    //! Reference to IO Service
    IOService* ioService = NULL;

    //! Time object.
    Time* TimeAct = NULL;

    //! Initializes TimeService
    //! @param ioservice The IOService reference.
    //!
    TimeService(IOService* ioservice){
        ioService = ioservice;
    }
};

#endif
