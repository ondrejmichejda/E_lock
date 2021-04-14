#ifndef TimeService_h
#define TimeService_h

#include "Arduino.h"
#include "ServiceBase.h"
#include "Time.h"
#include "PulseGenerator.h"
#include "IOService.h"

#define FREQ 600


class TimeService : public ServiceBase
{
public:
    IOService* ioService = NULL;
    Time* TimeAct = NULL;

    TimeService(IOService* ioservice){
        ioService = ioservice;
    }

private:
    PulseGenerator* Generator = NULL;

    void Init(){
        Generator = new PulseGenerator(FREQ);
        TimeAct = new Time(12, 23, 1);

        Status = true;
        Log("Initialized");
    }

    void Work(){
        if(Generator->On()){
            TimeAct->Tick();
            //Log(String(TimeAct->GetHour()) + ":" + TimeAct->GetMinute());
        }
    }
};

#endif
