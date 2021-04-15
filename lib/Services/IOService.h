#ifndef IOService_h
#define IOService_h

#include "Arduino.h"
#include "BaseService.h"
#include "Logger.h"
#include "Key.h"
#include "Display.h"

#define NUMBER_OF_KEYS 4

//! Class covering all IO periferies and it's functionalities.
class IOService : public BaseService, public ILoggable
{
private:
    Key* _keys[NUMBER_OF_KEYS];

    //! Initialization.
    void _init(){
        Key1 = new Key(5, "1");
        _keys[0] = Key1;

        Key2 = new Key(4, "2");
        _keys[1] = Key2;

        Key3 = new Key(7, "3");
        _keys[2] = Key3;

        Key4 = new Key(6, "4");
        _keys[3] = Key4;
        

        Display1 = new Display(2, 3);

        Logger::Log(NULL, this, Texts::Init);
    }

    //! Work to be done.
    void _work(){
        for (size_t i = 0; i < NUMBER_OF_KEYS; i++)
        {
            _keys[i]->Run();
        }
    }

    //! Failed.
    void _failed(){
        Logger::Log(NULL, this, Texts::Fail);
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

    String GetLogName(){
        return Name;
    }
};

#endif