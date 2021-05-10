/*
  RGBLED.h - Library for handle RGB LED modul.
*/
#ifndef RGBLED_h
#define RGBLED_h

#include "Arduino.h"
#include "TimeService.h"
#include "TOn.h"
#include "ILoggable.h"
#include "Logger.h"

//! Class to cover button functionality.
class RGBLED : public ILoggable
{
private:
	uint8_t _pin_r;
    uint8_t _pin_g;
    uint8_t _pin_b;
	TOn* _ton = NULL;
    TimeService* _timeService = NULL;

public:
	//! Initializes LED object.
	//! @param pin_r Pin for RED intensity.
    //! @param pin_g Pin for GREEN intensity.
    //! @param pin_b Pin for BLUE intesity.
	RGBLED(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b, TimeService* timeService){
        _pin_r = pin_r;
        _pin_g = pin_g;
        _pin_b = pin_b;
        pinMode(_pin_r, OUTPUT);
        pinMode(_pin_g, OUTPUT);
        pinMode(_pin_b, OUTPUT);

        _ton = new TOn(2000);
	}

    // Run method to enable timing functions.
    void Run(){
        if(_ton->Out){
            Off();
            _ton->In = false;
        }
        _ton->Run();
    }

    // Turn of light.
    void Off(){
        analogWrite(_pin_r, 0);
        analogWrite(_pin_g, 0);
        analogWrite(_pin_b, 0);
    }

    // Turn on light.
    void On(){
        On(255, 255, 255);
    }

    // Turn on light.
    //! @param r Red value.
    //! @param g Green value.
    //! @param b Blue value.
    void On(uint8_t r, uint8_t g, uint8_t b){
        _ton->In = true;
        analogWrite(_pin_r, r);
        analogWrite(_pin_g, g);
        analogWrite(_pin_b, b);
    }

    // Red light.
    void Red(){
        On(255, 0, 0);
    }

    // Green light.
    void Green(){
        On(0, 255, 0);
    }

	// Blue light.
    void Blue(){
        On(0, 0, 255);
    }

    String GetLogName(){
        return "RGB LED";
    }
};

#endif