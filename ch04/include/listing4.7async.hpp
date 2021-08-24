#include "headers.h"
#pragma once

int fun1(int data){
    return 2*data;
}


void listing4_7async_main(){
    std::future<int> f1 = std::async(fun1,5);
    std::cout<<"\n Returned value from future is::"<<f1.get();

    std::cout<<"\n listing4_7async_main ended...";
}