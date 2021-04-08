#include "Arduino.h"
#include "Key.h"
#include "Time.h"
#include "PulseGenerator.h"
#include "TOn.h"
#include "Display.h"

// Object declaration ->
Key key1(5, "1");
Key key2(4, "2");
Key key3(7, "3");
Key key4(6, "4");
Display display(2, 3);
Time time(18, 35, 1);
PulseGenerator gen(600);
// <-

// Functions declaration ->
void KeyMonitor();
// <-

// *************************************************************
// *************************** SETUP ***************************
// *************************************************************
void setup()
{
	// Serial comm setup
	Serial.begin(9600);
}

// *************************************************************
// *************************** LOOP ****************************
// *************************************************************
void loop()
{
	KeyMonitor();

	// time
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
}

// Functions definition ->
void KeyMonitor(){
	key1.Monitor();
	key2.Monitor();
	key3.Monitor();
	key4.Monitor();
}
// <-
