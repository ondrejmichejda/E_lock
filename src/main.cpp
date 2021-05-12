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

// *************************************************************
// *************************** LOOP ****************************
// *************************************************************
void loop()
{
    timeService->Run();
	ioService->Run();
    setupService->Run();
}

