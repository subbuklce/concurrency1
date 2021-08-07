#ifndef _DEADLOCK_FREE_MUTEX_H_
#define  _DEADLOCK_FREE_MUTEX_H_

#include "headers.h"

template <typename T>
class mystack{
std::stack<int> stack_data;
std::mutex mutex_stack_data;
std::stack<char>  char_stack_data;
std::mutex mutex_char_data;
public:
    void push(int idata, char ichar){
        std::lock(mutex_stack_data, mutex_char_data);
        std::lock_guard<std::mutex> l1(mutex_stack_data, std::adopt_lock);
        std::lock_guard<std::mutex> l2(mutex_char_data, std::adopt_lock);
        stack_data.push(idata);
        char_stack_data.push(ichar);

    }
    void print(){
        
        auto i =0;
        while(stack_data.size()){
            std::cout<<"\n"<<stack_data.top();
            stack_data.pop();
            
        }
        std::cout<<"\n char data is ::";
        i=0;
        while(char_stack_data.size()){
            
            std::cout<<"\n"<<char_stack_data.top();
            char_stack_data.pop();
        }
        
    }
};

void dead_lock_free_main_function(){
    mystack<int> object;
    for (auto i:{1,2,3,4,5})
        object.push(i,'a');

    object.print();
    
}
#endif