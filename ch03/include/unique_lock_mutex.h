#ifndef _UNIQUE_MUTEX_H_
#define _UNIQUE_MUTEX_H_

#include "headers.h"

struct sData{
    int idata;
    std::string mydata;
};

class swap_mutexs{
    std::string id;
    sData  data;
    mutable std::mutex m;
    public:
    swap_mutexs(std::string_view _id):id(_id){

    }
    std::unique_lock<std::mutex>  get_lock(){
        return std::unique_lock<std::mutex>(m, std::defer_lock);
        
    }
    void process_data(int idata, std::string_view sdata){
        get_lock();
        data.idata = idata;
        data.mydata = sdata;

    }
    void print(){
        std::cout<<"\n "<<id<<" data int::"<<data.idata<<" string is::"<<data.mydata;

    }
    friend void myswap(swap_mutexs &s1, swap_mutexs & s2){
        try{
            std::unique_lock<std::mutex> ul1(s1.get_lock());
            std::unique_lock<std::mutex> ul2(s2.get_lock());
            std::lock(ul1, ul2);
            std::swap(s1.data, s2.data);
        }
        catch(std::exception & e){
            std::cout<<"\n found an exception::"<<e.what();
        }
    }

};

void trasfer_mutex_main_function(){
    swap_mutexs s1("s1"), s2("s2");
    s1.process_data(2222, std::string("Hello world"));
    s2.process_data(4444, std::string("How are you?"));
    s1.print();
    s2.print();
    myswap(s2,s1);
    s1.print();
    s2.print();
 }


#endif