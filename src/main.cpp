#include "IOService.h"
#include "TimeService.h"
#include "SetupService.h"

//#include "SoftwareSerial.h"     //+
//SoftwareSerial RFID(8, 0);      //+

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
    //RFID.begin(9600);       

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

    /*
    if (RFID.available() > 0) {
        char receivedID[14];
        for (int i = 0; i < 14; i++) {
            receivedID[i] = RFID.read();
        }
        
        Serial.print("Nactene ID: ");

        for (int i = 1; i < 14; i++) {
            Serial.print(receivedID[i]);
            Serial.print(" ");
        }
    }
    */
    
}
