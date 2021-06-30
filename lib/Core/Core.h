/*
    Core.h  - Core class to cover all..
*/

#ifndef Core_h
#define Core_h

#include "IOService.h"
#include "AuthService.h"
#include "SerialService.h"
#include "StorageService.h"


class Core {

private:
    TimeService* timeService;
    StorageService* storageService;
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

        // Storage Service
        storageService = new StorageService(timeService);

        // IO Service
        ioService = new IOService(timeService);

        // Authentication Service
        authService = new AuthService(timeService, ioService, storageService);

        // Serial Service
        serialService = new SerialService(timeService, ioService, authService);

        char startText[] = "E-lock started";
        Logger::Log(timeService->TimeAct, NULL, startText);
    }   

    // Do the work of Core class.
    void Run(){
        timeService->Run();
        storageService->Run();
        ioService->Run();
        authService->Run();
        serialService->Run();
    } 
};

#endif