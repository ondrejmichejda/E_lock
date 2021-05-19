/*
    Core.h  - Core class to cover all..
*/

#ifndef Core_h
#define Core_h

#include "IOService.h"
#include "TimeService.h"
#include "AuthService.h"

class Core {

private:
    TimeService* timeService;
    IOService* ioService;
    AuthService* authService;

public:

    // Initializes core class.
    Core(){
        // Static classes init
        Logger::Setup(9600);

        // Time Service
        timeService = new TimeService();
        char timeName[] = "Time";
        timeService->Setup(timeName);

        // IO Service
        ioService = new IOService(timeService);
        char ioName[] = "IO";
        ioService->Setup(ioName);

        // Authentication Service
        authService = new AuthService(timeService, ioService);
        char authName[] = "Auth";
        authService->Setup(authName);

        char startText[] = "E-lock started";
        Logger::Log(timeService->TimeAct, NULL, startText);
    }   

    // Do the work of Core class.
    void Run(){
        timeService->Run();
        ioService->Run();
        authService->Run();

        Logger::Run();
    } 
};

#endif