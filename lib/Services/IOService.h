#ifndef IOService_h
#define IOService_h

#include "Arduino.h"
#include "ServiceBase.h"
#include "TimeService.h"
#include "Key.h"
#include "Display.h"

class IOService : public ServiceBase
{
public:
    Key Key1;
    Key Key2;
    Key Key3;
    Key Key4;
    Display Display1;
    TimeService _timeService;

    IOService(TimeService &timeService) : Key1(5, "1"), 
                    Key2(4, "2"), 
                    Key3(7, "3"), 
                    Key4(6, "4"),
                    Display1(2, 3){
        _timeService = timeService;
    }

private:
    
    void Init(){
        Status = true;
        Log("Initialized");
    }

    void Work(){
        Key1.Monitor();
        Key2.Monitor();
        Key3.Monitor();
        Key4.Monitor();

        Display1.Run(_timeService.Time1);

        //Serial.println(_timeService.Time1.GetTotalMin());

        if(_timeService.Time1.Changed()){
            Display1.Update(_timeService.Time1);
        }
    }
};

#endif