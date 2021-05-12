#ifndef TimeService_h
#define TimeService_h

#include "Arduino.h"
#include "BaseService.h"
#include "ILoggable.h"
#include "Logger.h"
#include "RTC.h"

//! Class covering Time services.
class TimeService : public BaseService, public ILoggable
{
private:

    //! Initialization.
    void _init(){
        TimeAct = new RTC();
        Logger::Log(TimeAct, this, initText);
    }

    //! Work to be done.
    void _work(){}

    void _failed(){
        Logger::Log(TimeAct, this, failText);
    }

public:
    // Actual Time object.
    RTC* TimeAct;

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
