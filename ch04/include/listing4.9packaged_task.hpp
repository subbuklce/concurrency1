#pragma once

#include "headers.h"


//using signature = int(int, int);
using signature = int(void);
std::deque<std::packaged_task<signature>> Tasks;
std::mutex mtx;
std::condition_variable mcv;

template <typename func >
std::future<typename func::result_type> add_task(func Fn){
    std::packaged_task<signature> pt(Fn);
    std::future<typename func::result_type> ft= pt.get_future(); 
    std::lock_guard<std::mutex> lg(mtx);
    Tasks.push_front(std::move(pt));
    mcv.notify_one();
    return ft;
}

void Process_tasks(){
    while(true){
        std::packaged_task<signature> task;
        
        {
            std::unique_lock<std::mutex> ul(mtx);
            mcv.wait(ul, [&]{ return !Tasks.empty();});
            task = std::move(Tasks.front());
            Tasks.pop_front();
        }
        task();
    }
}

int sample_func(void){
    std::cout<<"\n The sample function got called from packaged_task deque start...";
    std::this_thread::sleep_for(1s);
    std::cout<<"\n The sample function got called from packaged_task deque end...";
    return 20*1;
}

void packaged_task_main(){
    std::thread scheduler = std::thread(Process_tasks);
    scope_guard sg(std::move(scheduler));
    for(auto i:{1,2,3,4,5,6}){
        auto rt = add_task<std::function<signature>>(sample_func);
        std::this_thread::sleep_for(500ms);
        std::cout<<"\n The output data is::"<<rt.get();
    }
    
}
