/*
  CardReader125.h - Card reader for 125kHz comm.
*/
#ifndef CardReader125_h
#define CardReader125_h

#include "ICardReader.h"
#include "SoftwareSerial.h"
#include "ILoggable.h"
#include "Logger.h"
#include "TimeService.h"

class CardReader125 : public ICardReader, public ILoggable
{
private:
    SoftwareSerial* _serial;
    TimeService* _timeService;
    TOn* _readTOn;
    String _msg;
    bool _newData;
    bool _enableRead;

    // Clear buffer and enable reading
    void _clearBuffer(){
        if(!_enableRead){
            _enableRead = true;
            Logger::Log(_timeService->TimeAct, this, "Reading enabled");
        }
    }

public:
    //! Initializes card reader object.
    //! @param rx Receiver pin
    //!
    CardReader125(uint8_t rx, TimeService* timeService, long commSpeed = 9600){
        _timeService = timeService;
        _readTOn = new TOn(2000);
        _serial = new SoftwareSerial(rx, 0);
        _serial->begin(commSpeed);
        _newData = false;
        _enableRead = true;
    }

    // Method of main cyclic function
	void Run(){
        if(_serial->available() > 0){
            if(_enableRead){
                int i = 0;
                _msg = "";
                while (_serial->available() > 0) {
                    int b = _serial->read();
                    if(i<14){
                        _msg += String(b);
                        i++;
                    }
                }
                Serial.println(this->GetLogName());
                Logger::Log(_timeService->TimeAct, this, _msg);
                _newData = true;
                _enableRead = false;
            }
            else{
                while (_serial->available() > 0) {_serial->read();}
            }
        }

        if(_newData){
            _readTOn->In = true;
        }

        if(_readTOn->Out){
            _clearBuffer();
            _readTOn->In = false;
        }

        _readTOn->Run();
    }

    //! Return data on new data arrival
    //! @return True if new data arrived
    bool NewData(){
        return _newData;
    }

    //! Returns array of new data and clear buffer
    //! @return Id in int array.
    String GetData(){
        _newData = false;
        return _msg;
    }

    String GetLogName(){
        return "Card Reader";
    }
};

#endif