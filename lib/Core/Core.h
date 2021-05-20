/*
    Core.h  - Core class to cover all..
*/

#ifndef Core_h
#define Core_h

#include "IOService.h"
#include "TimeService.h"
#include "AuthService.h"
#include "SerialService.h"

class Core {

private:
    TimeService* timeService;
    IOService* ioService;
    AuthService* authService;
    SerialService* serialService;

public:

    // Initializes core class.
    Core(){
        // Static classes init
        Logger::Setup(9600);

        // Time Service
        timeService = new TimeService();

        // IO Service
        ioService = new IOService(timeService);

        // Authentication Service
        authService = new AuthService(timeService, ioService);

        // Serial Service
        serialService = new SerialService(timeService);

        char startText[] = "E-lock started";
        Logger::Log(timeService->TimeAct, NULL, startText);
    }   

    // Do the work of Core class.
    void Run(){
        timeService->Run();
        ioService->Run();
        authService->Run();
        serialService->Run();
    } 
};

#endif