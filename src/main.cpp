#include "IOService.h"
#include "TimeService.h"
#include "SetupService.h"

// Services declaration ->
TimeService* timeService;
IOService* ioService;
SetupService* setupService;
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
}

// *************************************************************
// *************************** LOOP ****************************
// *************************************************************
void loop()
{
    timeService->Run();
	ioService->Run();
    setupService->Run();
}

