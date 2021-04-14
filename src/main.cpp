#include "Arduino.h"
#include "PulseGenerator.h"
#include "IOService.h"
#include "TimeService.h"

// Services declaration ->
IOService* ioService = NULL;
TimeService* timeService = NULL;
// <-

// *************************************************************
// *************************** SETUP ***************************
// *************************************************************
void setup()
{
	// Serial comm setup
	Serial.begin(9600);

	// IOService
	ioService = new IOService();
	ioService->Setup("IO Service");

	// TimeService
	timeService = new TimeService(ioService);
	timeService->Setup("Time Service");
}

// *************************************************************
// *************************** LOOP ****************************
// *************************************************************
void loop()
{
	ioService->Run();
	timeService->Run();
}
