#ifndef IOService_h
#define IOService_h

#include "Arduino.h"
#include "ServiceBase.h"
#include "Key.h"

class IOService : ServiceBase
{
public:
    Key Key1;
    Key Key2;
    Key Key3;
    Key Key4;
    IOService(){
        Key1 = Key(5, "1");
        Key2 = Key(4, "2");
        Key key3(7, "3");
        Key key4(6, "4");
        //test
    }
    void Run(){
        
    }
	
};

#endif