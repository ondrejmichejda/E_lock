#include "IOService.h"
#include "TimeService.h"
#include "SetupService.h"

// Services declaration ->
TimeService* timeService = NULL;
IOService* ioService = NULL;
SetupService* setupService = NULL;
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
