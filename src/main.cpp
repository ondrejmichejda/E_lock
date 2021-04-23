#include "IOService.h"
#include "TimeService.h"
#include "SetupService.h"

#include "CardReader125.h"

// Services declaration ->
TimeService* timeService;
IOService* ioService;
SetupService* setupService;

CardReader125* reader;
// <-

// *************************************************************
// *************************** SETUP ***************************
// *************************************************************
void setup()
{   
    // Static classes init
    Logger::Setup(9600);

    // Time Service
	timeService = new TimeService();
	timeService->Setup("Time Service");

	// IO Service
	ioService = new IOService(timeService);
	ioService->Setup("IO Service");

    // Setup Service
    setupService = new SetupService(timeService, ioService);
    setupService->Setup("Setup Service");

    Logger::Log(timeService->TimeAct, NULL, "E-Lock on Arduino started");

    reader = new CardReader125(8, timeService);
}

// *************************************************************
// *************************** LOOP ****************************
// *************************************************************
void loop()
{
    timeService->Run();
	ioService->Run();
    setupService->Run();

    reader->Run();

    if(ioService->Key1->Click){
        reader->ClearBuffer();
    }
}

