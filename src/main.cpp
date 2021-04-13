#include "Arduino.h"
#include "PulseGenerator.h"
#include "IOService.h"
#include "TimeService.h"

// Services declaration ->

TimeService _timeService;
IOService _ioService(_timeService);
// <-



// *************************************************************
// *************************** SETUP ***************************
// *************************************************************
void setup()
{
	// Serial comm setup
	Serial.begin(9600);

	_timeService = TimeService();
	_timeService.Setup("TimeService");

	_ioService = IOService(_timeService);
	_ioService.Setup("IOService");
}

// *************************************************************
// *************************** LOOP ****************************
// *************************************************************
void loop()
{
	_timeService.Run();
	_ioService.Run();

	Serial.println(_ioService._timeService.Time1.GetTotalMin());

	/*// times
	if(gen.On()){
		time.Tick();
	}

	if (time.Changed()){
		if(time.GetEditMode() || time.GetPwdMode()) return;
		display.Update(time);
	}

	// check for entering password mode
	if(key1.Long){
		if(time.GetEditMode() || time.GetPwdMode()){
			time.SetPwdMode(false);
			time.SetEditMode(false);
		}
		else
			time.SetPwdMode(true);
	}

	// check for entering edit mode
	if(time.GetPwdMode()){
		// check key sequence
		if(key1.Click){
			time.SetEditMode(true);
		}
	}

	if(time.GetEditMode()){
		if(key1.Click){
			time.Modify(true, true);	// + hour
			display.Update(time);
			gen.reset();
		}
			
		if(key2.Click){
			time.Modify(true, false);	// - hour
			display.Update(time);
			gen.reset();
		}
			
		if(key3.Click){
			time.Modify(false, true);	// + minute
			display.Update(time);
			gen.reset();
		}
			
		if(key4.Click){
			time.Modify(false, false);	// - minute
			display.Update(time);
			gen.reset();
		}
	}

	display.EditMode = time.GetEditMode();
	display.PwdMode = time.GetPwdMode();
	display.Run();
	*/
}
