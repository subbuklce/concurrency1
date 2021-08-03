//
// Created by subrahmanyam on 31/07/21.
//

#ifndef CH02_LIST2_3_RAII_H
#define CH02_LIST2_3_RAII_H
#include "headers.h"

//thread_guard class is important in this file
//in case t.join() is not called in main_function then any exception would
// terminate the thread which indirectly leads to resource leak.
// option 1: mention t.join() in each exception
// option 2: make thread object as joinable in its destructior
// override that functionality with thread_guard destructor.

struct slong{
    int& outside_var;
    slong(int& var):outside_var(var){}
    void operator()(){
        for (int i = 0; i < 1000000; ++i) {
            std::cout<<"";
        }
    }

};


class thread_guard{
std::thread &t1;
public:
    explicit thread_guard(std::thread& _fun): t1(_fun){
        if(t1.joinable() == false){
            throw std::logic_error("No thread is attached really!");
        }
    }
    ~thread_guard(){
        if(t1.joinable()){
            t1.join();
        }
    }
    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete;
};

class mythread:public std::thread{
public:
    mythread(){}
    ~mythread(){
        if(this->joinable()){
            this->join();
        }
    }
};

void list2_main_function(){
    int local_data = 10;
    //std::thread tt(my_function,local_data);
    slong background_task(local_data);
    std::thread tt(background_task);
    thread_guard tg(tt);

    std::cout<<"\n in list2_main_function end";
}

#endif //CH02_LIST2_3_RAII_H
