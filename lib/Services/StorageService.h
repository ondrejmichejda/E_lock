/*
    StorageService.h - Stores data to SD memory card.
*/

#ifndef StorageService_h
#define StorageService_h

#include "SPI.h"
#include "SD.h"

#define sd_CS_pin 10    //Hard defined communication pin, pin is on shield module

class StorageService : public BaseService, ILoggable{

private:
    TimeService* _timeService;
    bool _sdOk = false;

    //! Initialization.
    void _init(){
        // check sd card connection
        // if (!SD.begin(sd_CS_pin)) {
        //     char failSD[] = "Missing or malfunction of SD card.";
        //     Logger::Log(_timeService->TimeAct, this, failSD);
        //     return;
        // }
        _sdOk = true;

        char folder[] = "abc";
        // CreateFolder(folder);
        Logger::Log(_timeService->TimeAct, this, initText);
    }

    //! Work to be done.
    void _work(){
        
    }

    //! Failed.
    void _failed(){
        Logger::Log(_timeService->TimeAct, this, failText);
    }
public:

    StorageService(TimeService* timeService){
        _timeService = timeService;
        _init();
    }

    //! Creates folder if not exists
    //! @param fname Name of folder
    void CreateFolder(char* fname){
        if(_sdOk)
            SD.mkdir(fname);
    }

    String GetLogName(){
        return "Storage Service";
    }
};

#endif