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
        char k1Name[] = "1";
        Key1 = new Key(5, k1Name);
        _keys[0] = Key1;

        char k2Name[] = "2";
        Key2 = new Key(4, k2Name);
        _keys[1] = Key2;

        char k3Name[] = "3";
        Key3 = new Key(7, k3Name);
        _keys[2] = Key3;

        char k4Name[] = "4";
        Key4 = new Key(6, k4Name);
        _keys[3] = Key4;
        
        Display1 = new Display(2, 3);

        Reader = new CardReader125(8);

        Led = new RGBLED(9, 10, 11);

        Logger::Log(_timeService->TimeAct, this, initText);
    }

    //! Work to be done.
    void _work(){
        for (size_t i = 0; i < NUMBER_OF_KEYS; i++)
        {
            _keys[i]->Run();
            if(_keys[i]->Click) Logger::LogStr(_timeService->TimeAct, this, "Key " + String(_keys[i]->Name) + " Click");
            if(_keys[i]->Long) Logger::LogStr(_timeService->TimeAct, this, "Key " + String(_keys[i]->Name) + " Hold");
        }

        Reader->Run();
        if(Reader->NewData()) {
            String code = Reader->GetData();

            Logger::LogStr(_timeService->TimeAct, this, "Card=" + code);
        }
        Led->Run();
    }

    //! Failed.
    void _failed(){
        Logger::Log(_timeService->TimeAct, this, failText);
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
        Key1 = NULL;
        Key2 = NULL;
        Key3 = NULL;
        Key4 = NULL;
        Display1 = NULL;
        Reader = NULL;
        Led = NULL;
    }

    String GetLogName(){
        return Name;
    }
};

#endif