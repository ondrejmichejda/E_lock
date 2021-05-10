#ifndef IOService_h
#define IOService_h

#include "Arduino.h"
#include "BaseService.h"
#include "TimeService.h"
#include "Logger.h"
#include "Key.h"
#include "Display.h"
#include "CardReader125.h"
#include "RGBLED.h"

#define NUMBER_OF_KEYS 4

//! Class covering all IO periferies and it's functionalities.
class IOService : public BaseService, public ILoggable
{
private:
    Key* _keys[NUMBER_OF_KEYS];
    TimeService* _timeService = NULL;

    //! Initialization.
    void _init(){
        Key1 = new Key(5, "1", _timeService);
        _keys[0] = Key1;

        Key2 = new Key(4, "2", _timeService);
        _keys[1] = Key2;

        Key3 = new Key(7, "3", _timeService);
        _keys[2] = Key3;

        Key4 = new Key(6, "4", _timeService);
        _keys[3] = Key4;
        
        Display1 = new Display(2, 3);

        Reader = new CardReader125(8, _timeService);

        Led = new RGBLED(9, 10, 11, _timeService);

        Logger::Log(_timeService->TimeAct, this, Texts::Init);
    }

    //! Work to be done.
    void _work(){
        for (size_t i = 0; i < NUMBER_OF_KEYS; i++)
        {
            _keys[i]->Run();
        }

        Reader->Run();
        Led->Run();
    }

    //! Failed.
    void _failed(){
        Logger::Log(_timeService->TimeAct, this, Texts::Fail);
    }

public:
    //! Keys definitions
    Key* Key1;
    Key* Key2;
    Key* Key3;
    Key* Key4;

    //! Display definition
    Display* Display1;

    // Card reader
    CardReader125* Reader;

    //RGB LED
    RGBLED* Led;

    //! Initializes IOService.
    //! @param timeService Reference to TimeService.
    //!
    IOService(TimeService* timeService){
        _timeService = timeService;
    }

    String GetLogName(){
        return Name;
    }
};

#endif