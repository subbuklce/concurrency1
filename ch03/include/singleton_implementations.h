#ifndef _SINGLETON_IMPLEMENTATIONS_H_
#define _SINGLETON_IMPLEMENTATIONS_H_
#include "headers.h"

class cLogger{
     std::string mfilepath;
    public:
    cLogger(const std::string_view file):mfilepath(file){};
    void mLog(std::string){};
    auto filepath() const{return mfilepath;};   

};

std::shared_ptr<cLogger> Log;
std::mutex logger_mutex;
std::once_flag onceflag;




void GetLoggerInstance_doublecheck(std::string_view& ifilepath){
    if(!Log){
        std::lock_guard<std::mutex> ll(logger_mutex);
        if(!Log){
            Log.reset(new cLogger(ifilepath));
        }
    }
    
}
void GetInstance(std::string_view ifilepath){
    Log.reset(new cLogger(ifilepath));
}

void CreateInstance(std::string_view ifilepath){

    std::cout<<"\n Thread ID::"<<std::this_thread::get_id();
    if(Log){
        std::cout<<"\n  File path is "<<Log->filepath()<<"\n Printed by id"<<std::this_thread::get_id();
    }
    else{
        std::cout<<"\n shared pointer is null so creating new instance..."<<std::this_thread::get_id();
        try{
            std::call_once(onceflag, GetInstance,ifilepath);
            
            std::cout<<"\n Created instance by "<<std::this_thread::get_id();
        }
        catch(std::exception &e){
            std::cout<<"\n caught an exception here "<<e.what();

        }
    }
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(5000ms);
}

void CreateInstance_version2(std::string_view ifilepath){
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1000ms);
    std::call_once(onceflag, GetInstance,ifilepath);
    

}
void singleton_main_function(){    
    const std::string logpath = "/tmp/mylogger.log";
    std::vector<std::thread> vThread;
    for(auto i=0;i<5;++i){
        vThread.emplace_back(std::thread(CreateInstance,logpath));
        //vThread.emplace_back(std::thread(CreateInstance_version2,logpath));
    }
    for_each(vThread.begin(), vThread.end(), std::mem_fn(&std::thread::join));
}



#endif