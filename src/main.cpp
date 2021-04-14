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

	ioService = new IOService();
	ioService->Setup("IO Service");

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

	// test comment from work laptop
	if(timeService->ioService->Key1->Click){
		Serial.println("click from time service");
	}
	
}
