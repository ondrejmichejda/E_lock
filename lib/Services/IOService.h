#ifndef IOService_h
#define IOService_h

#include "Arduino.h"
#include "ServiceBase.h"
#include "Key.h"
#include "Display.h"

class IOService : public ServiceBase
{
public:
    Key* Key1 = NULL;
    Key* Key2 = NULL;
    Key* Key3 = NULL;
    Key* Key4 = NULL;
    Display Display1;

    IOService() : Display1(2, 3){}

private:
    
    void Init(){
        Key1 = new Key(5, "1");
        Key2 = new Key(4, "2");
        Key3 = new Key(7, "3");
        Key4 = new Key(6, "4");

        Status = true;
        Log("Initialized");
    }

    void Work(){
        Key1->Monitor();
        Key2->Monitor();
        Key3->Monitor();
        Key4->Monitor();
    }
};

#endif