#ifndef TimeService_h
#define TimeService_h

#include "Arduino.h"
#include "ServiceBase.h"
#include "Time.h"
#include "PulseGenerator.h"

class TimeService : public ServiceBase
{
public:
    Time Time1;

    TimeService() : Time1(9, 41, 1), 
                    Generator(600){
    }

private:
    PulseGenerator Generator;

    void Init(){
        Status = true;
        Log("Initialized");
    }

    void Work(){
        if(Generator.On()){
            Time1.Tick();
            //Log(String(Time1.GetHour()) + ":" + Time1.GetMinute());
        }
    }
};

#endif
