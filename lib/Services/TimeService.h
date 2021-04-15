#ifndef TimeService_h
#define TimeService_h

#include "Arduino.h"
#include "BaseService.h"
#include "ILoggable.h"
#include "Logger.h"
#include "Time.h"
#include "PulseGenerator.h"

#define FREQ 600

//! Class covering Time services.
class TimeService : public BaseService, public ILoggable
{
private:
    PulseGenerator* Generator = NULL;

    //! Initialization.
    void _init(){
        Generator = new PulseGenerator(FREQ);
        TimeAct = new Time(12, 23, 1);

        Logger::Log(TimeAct, this, Texts::Init);
    }

    //! Work to be done.
    void _work(){
        if(Generator->On()){
            TimeAct->Tick();
        }
    }

    void _failed(){
        //log
    }

public:
    //! Time object.
    Time* TimeAct = NULL;

    //! Initializes TimeService
    //! @param ioservice The IOService reference.
    //!
    TimeService(){}

    //! Get Name
    //! @return Name of this loggable object.
    //!
    String GetLogName(){
        return Name;
    }
};

#endif
