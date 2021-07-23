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
        // Static classes init
        Logger::Setup(9600);

        pinMode(sd_CS_pin, OUTPUT);
        //check sd card connection
        if (!SD.begin(sd_CS_pin)) {
            char failSD[] = "Missing or malfunction of SD card.";
            Log(_timeService->TimeAct, this, failSD);
            while(1);
        }
        _sdOk = true;

        Log(_timeService->TimeAct, this, initText);
    }

    //! Work to be done.
    void _work(){
        
    }

    //! Failed.
    void _failed(){
        Log(_timeService->TimeAct, this, failText);
    }
public:

    StorageService(TimeService* timeService){
        _timeService = timeService;
        _init();
    }

    void Log(RTC* rtc, ILoggable* object, String msg){
        File f = SD.open(LOGFILE, FILE_WRITE);
        String logText = Logger::LogStr_(rtc, object, msg);
        //if file succesfuly open (created), do write
        if (f) {
            f.println(logText);
            f.close();
        }
    }

    
    bool IsUserInList(String cardCode){
        File f = SD.open(USERFILE, FILE_READ);
        String stream;
        while(f.available()){
            stream += char(f.read());
        }
        if (stream.indexOf(cardCode) > -1){
            //user is in list
            return true;
        }
        else{
            return false;
        }
    }

    bool AddUser(String cardCode){
        if (IsUserInList(cardCode)){
            Log(_timeService->TimeAct, this, "User already added.");
            return false;
        }
        
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