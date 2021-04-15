#include "IOService.h"
#include "TimeService.h"

// Services declaration ->
TimeService* timeService = NULL;
IOService* ioService = NULL;
// <-

// *************************************************************
// *************************** SETUP ***************************
// *************************************************************
void setup()
{   
    // Logger init
    Logger::Setup();

    // TimeService
	timeService = new TimeService();
	timeService->Setup("Time Service");

	// IOService
	ioService = new IOService();
	ioService->Setup("IO Service");
}

// *************************************************************
// *************************** LOOP ****************************
// *************************************************************
void loop()
{
    timeService->Run();
	ioService->Run();
}
