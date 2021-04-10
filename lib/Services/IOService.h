#ifndef IOService_h
#define IOService_h

#include "Arduino.h"
#include "ServiceBase.h"
#include "Key.h"

class IOService : public ServiceBase
{
public:
    Key Key1;
    Key Key2;
    Key Key3;
    Key Key4;

    IOService() : ServiceBase(), Key1(5, "1"), Key2(4, "2"), Key3(7, "3"), Key4(6, "4"){
    }

protected:

    void Init(){
        Status = true;
        Log("Initialized");
    }

    void Work(){
        Key1.Monitor();
        Key2.Monitor();
        Key3.Monitor();
        Key4.Monitor();

        if(Key1.Click){
            Status = false;
        }
    }
};

#endif