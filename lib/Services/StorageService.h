#ifndef StorageService_h
#define StorageService_h

class StorageService : public BaseService, ILoggable{

private:
    TimeService* _timeService;

    //! Initialization.
    void _init(){
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

    String GetLogName(){
        return "Storage Service";
    }
};

#endif