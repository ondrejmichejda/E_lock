/*
  CardReader125.h - Card reader for 125kHz comm.
*/
#ifndef CardReader125_h
#define CardReader125_h

#include "ICardReader.h"
#include "SoftwareSerial.h"

class CardReader125 : public ICardReader
{
private:
    SoftwareSerial* _serial;
    TOn* _readTOn;
    int _msg[12];
    bool _newData;
    bool _enableRead;
    String _code;

    // Clear buffer and enable reading
    void _clearBuffer(){
        if(!_enableRead){
            _enableRead = true;
        }
    }

public:
    //! Initializes card reader object.
    //! @param rx Receiver pin
    //!
    CardReader125(uint8_t rx, long commSpeed = 9600){
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
                while (_serial->available() > 0) {
                    int b = _serial->read();
                    if(i<13 && i>1){
                        _msg[i-2] = b;
                        //Serial.print(b);
                    }
                    i++;
                }
                
                _code = "";
                for (size_t i = 0; i < 11; i++)
                {
                    _code += String(_msg[i]);
                }
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
        return _code;
    }
};

#endif