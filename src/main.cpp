#include "Arduino.h"
#include "PulseGenerator.h"
#include "IOService.h"
//#include "TimeService.h"

// Services declaration ->
IOService* _ioService = NULL;
TimeService* _timeService = NULL;
// <-

// *************************************************************
// *************************** SETUP ***************************
// *************************************************************
void setup()
{
	// Serial comm setup
	Serial.begin(9600);

	_ioService = new IOService();
	_ioService->Setup("IO Service");

	_timeService = new TimeService();
	_timeService->Setup("Time Service");
}

// *************************************************************
// *************************** LOOP ****************************
// *************************************************************
void loop()
{
	_ioService->Run();
	_timeService->Run();
}
