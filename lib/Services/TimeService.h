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
        TimeAct = new Time(0, 0, 1);

        Logger::Log(TimeAct, this, Texts::Init);
    }

    //! Work to be done.
    void _work(){
        if(Generator->On()){
            TimeAct->Tick();
            // Logger::Log(TimeAct, this, "");
        }

    }

    void _failed(){
        //log
    }

public:
    // Actual Time object.
    Time* TimeAct = NULL;

    // Editable Time object.
    Time* TimeEdit = NULL;

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

    // Store copy of actual time in edit time
    void SetTimeEdit(){
        TimeEdit = new Time(TimeAct->GetTimeInt(), 1);
    }

    // Overrides act time with edit time
    void SetTimeAct(){
        TimeAct = new Time(TimeEdit->GetTimeInt(), 1);
    }
};

#endif
