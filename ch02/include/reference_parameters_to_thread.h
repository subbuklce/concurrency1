//
// Created by subrahmanyam on 31/07/21.
//

#ifndef CH02_REFERENCE_PARAMETERS_TO_THREAD_H
#define CH02_REFERENCE_PARAMETERS_TO_THREAD_H
#include "headers.h"

void myfunction(int& data){
    data += 5;
}

void reference_main_function(){
    std::vector<std::thread> vector_of_threads;
    int local_data = 1200;
    using my_thread = std::thread;
    std::thread t1 (myfunction, std::ref(local_data));
    vector_of_threads.push_back(std::move(t1));
    std::cout<<"\n Call by value ::"<<local_data;

    std::for_each(vector_of_threads.begin(),vector_of_threads.end(),[](std::thread& t){
        if(t.joinable()){ t.join();};
    });
    std::cout<<"\n Call by value ::"<<local_data;
}
#endif //CH02_REFERENCE_PARAMETERS_TO_THREAD_H
