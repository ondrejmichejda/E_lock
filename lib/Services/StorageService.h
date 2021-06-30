/*
    StorageService.h - Stores data to SD memory card.
*/

#ifndef StorageService_h
#define StorageService_h

#include "SPI.h"
#include "SD.h"

#define sd_CS_pin 53                
#define LOGFILE "log.txt"
#define USERFILE "users.txt"
#define DELIMITER ";"

class StorageService : public BaseService, ILoggable{

private:
    TimeService* _timeService;
    bool _sdOk = false;

    //! Initialization.
    void _init(){
        pinMode(sd_CS_pin, OUTPUT);
        //check sd card connection
        if (!SD.begin(sd_CS_pin)) {
            char failSD[] = "Missing or malfunction of SD card.";
            Logger::Log(_timeService->TimeAct, this, failSD);
            while(1);
        }
        _sdOk = true;

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

    void CreateLog(String msg){
        File f = SD.open(LOGFILE, FILE_WRITE);

        //if file succesfuly open (created), do write
        if (f) {
            f.println(msg);
            f.close();
        }
    }

    String GetUsers(){
        File f = SD.open(USERFILE, FILE_READ);
        String stream;
        while(f.available()){
            stream += char(f.read());
        }
        return stream;
    }

    bool AddUser(String cardCode){
        File f = SD.open(USERFILE, FILE_WRITE);

        //if file succesfuly open (created), do write
        if (f) {
            f.print(cardCode);
            f.print(DELIMITER);
            f.close();
            return true;
        }
        else{
            return false;
        }
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