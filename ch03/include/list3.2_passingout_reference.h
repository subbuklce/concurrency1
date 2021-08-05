//
// Created by subrahmanyam on 05/08/21.
//

#ifndef CH03_LIST3_2_PASSINGOUT_REFERENCE_H
#define CH03_LIST3_2_PASSINGOUT_REFERENCE_H
#include "headers.h"

class some_data{
public:
    int idata;
    std::string sData;

    some_data():idata(10), sData("some data in it"){

    }
};

class mutext_wrapper{
    some_data l;
    std::mutex m;
public:
    void get_data_outside(some_data** iOutside){
        std::lock_guard<std::mutex> mutex_lock(m);
        *iOutside = &l;
    }
    template <typename Fun>
    void give_data_reference(Fun custom_function){
        std::lock_guard<std::mutex> mutex_lock(m);
        custom_function(l);
    }
    void print(){
        std::cout<<"\n data is "<<l.idata<<"\t "<<l.sData;
    }

};
some_data * outsider;
void custom_function(some_data & data){
    outsider = &data;

}

void list32_main_function(){
    mutext_wrapper mw;
    some_data *some;
    mw.get_data_outside(&some);
    some->idata = 20;
    some->sData = "Hello world";
    mw.print();

    mw.give_data_reference(custom_function);
    outsider->sData = "This is modified using custom function";
    outsider->idata = 1000;
    mw.print();
}

#endif //CH03_LIST3_2_PASSINGOUT_REFERENCE_H
