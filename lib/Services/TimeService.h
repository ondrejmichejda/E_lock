#ifndef TimeService_h
#define TimeService_h

#include "BaseService.h"
#include "RTC.h"

//! Class covering Time services.
class TimeService : public BaseService, public ILoggable
{
private:

    //! Initialization.
    void _init(){
        TimeAct = new RTC();
    }

    //! Work to be done.
    void _work(){}

    void _failed(){
    }

public:
    // Actual Time object.
    RTC* TimeAct;

    //! Initializes TimeService
    //! @param ioservice The IOService reference.
    //!
    TimeService(){
        TimeAct = NULL;

        _init();
    }

    //! Get Name
    //! @return Name of this loggable object.
    //!
    String GetLogName(){
        return "Time Service";
    }
};

#endif
