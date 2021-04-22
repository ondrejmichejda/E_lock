#include <SoftwareSerial.h> 
#include "IOService.h"
#include "TimeService.h"
#include "SetupService.h"

SoftwareSerial RFID(8, 0);      //+

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
    RFID.begin(9600);       

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

    Logger::Log(timeService->TimeAct, NULL, "E Lock on Arduino started");
}

// *************************************************************
// *************************** LOOP ****************************
// *************************************************************
void loop()
{
    timeService->Run();
	ioService->Run();
    setupService->Run();

    Logger::Log(String(RFID.available()));
    for (size_t i = 0; i < 14; i++)
    {
        RFID.read();
    }
    
    
}


// // připojení knihovny SoftwareSerial
// #include "Arduino.h"
// #include <SoftwareSerial.h>
// // inicializace RFID z knihovny SoftwareSerial
// SoftwareSerial RFID(8, 0);

// void setup() {
//   RFID.begin(9600);
//   Serial.begin(9600);
// }

// void loop() {
//     Serial.println(String(RFID.available()));
// }
