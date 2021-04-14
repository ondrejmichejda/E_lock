#ifndef IOService_h
#define IOService_h

#include "Arduino.h"
#include "BaseService.h"
#include "Key.h"
#include "Display.h"

//! Class covering all IO periferies and it's functionalities.
class IOService : public BaseService
{
private:
    //! Initialization.
    void _init(){
        Key1 = new Key(5, "1");
        Key2 = new Key(4, "2");
        Key3 = new Key(7, "3");
        Key4 = new Key(6, "4");

        Display1 = new Display(2, 3);

        _status = true;
        _log("Initialized");
    }

    //! Work to be done.
    void _work(){
        Key1->Run();
        Key2->Run();
        Key3->Run();
        Key4->Run();
    }

public:
    //! Keys definitions
    Key* Key1 = NULL;
    Key* Key2 = NULL;
    Key* Key3 = NULL;
    Key* Key4 = NULL;

    //! Display definition
    Display* Display1;

    //! Initializes IOService.
    IOService(){}
};

#endif