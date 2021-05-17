/*
    Core.h  - Core class to cover all..
*/

#ifndef Core_h
#define Core_h

#include "IOService.h"
#include "TimeService.h"
#include "SetupService.h"

class Core {

private:
    TimeService* timeService;
    IOService* ioService;
    SetupService* setupService;

public:
    Core(){
        // Static classes init
        Logger::Setup(9600);

        // Time Service
        timeService = new TimeService();
        char timeName[] = "Time Service";
        timeService->Setup(timeName);

        // IO Service
        ioService = new IOService(timeService);
        char ioName[] = "IO Service";
        ioService->Setup(ioName);

        // Setup Service
        setupService = new SetupService(timeService, ioService);
        char setupName[] = "Setup Service";
        setupService->Setup(setupName);

        char startText[] = "E-lock on Arduino started";
        Logger::Log(timeService->TimeAct, NULL, startText);
    }   

    void Run(){
        timeService->Run();
        ioService->Run();
        setupService->Run();
    } 
};

#endif