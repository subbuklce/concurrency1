//
// Created by subrahmanyam on 05/08/21.
//

#ifndef CH03_LISTING3_4_THREAD_SAFE_STACK_H
#define CH03_LISTING3_4_THREAD_SAFE_STACK_H
#include "headers.h"

struct empty_stack: public std::exception
{
    virtual const char* what() const throw();
};

template <typename T>
class Stack{
    std::stack<T> stack_data;
    mutable std::mutex m;
public:
    Stack(){};
    Stack(const Stack& lhs){
        if(this == &lhs){
            throw(" copy constructor on same object!!");
            return;
        }
        std::lock_guard<std::mutex> getlock(lhs.m);
        this->stack_data = lhs.stack_data;
    }
    Stack& operator=(const Stack& lhs) = delete; // delete assignment constructor meaning object is not copying using =
    int size(){
        std::lock_guard<std::mutex> getlock(this->m);
        return stack_data.size();
    }
    void push(T idata){
        std::lock_guard<std::mutex> lg(m);
        stack_data.push(idata);
    }
    void pop(T& oData){
        if(this->stack_data.empty()) throw("not correct");// empty_stack();  - Not sure why this is not working as per example.
        oData = stack_data.top();
        stack_data.pop();
    }
    std::shared_ptr<T> pop(){
        std::lock_guard<std::mutex> lg(m);
        if(stack_data.empty()) throw std::logic_error("No more elements exists in stack!!"); // empty_stack();
        std::shared_ptr<T> out = std::make_shared<T>(stack_data.top());
        stack_data.pop();
        return out;

    }
};


void list_3_4_main_function(){
    Stack<int> s;
    s.push(123);
    //s = s;   use of deleted function
    Stack<int> d = s;
    int k =0;
    //s.pop(k);
    s.pop(k);
    std::shared_ptr<int> l = s.pop();
}

#endif //CH03_LISTING3_4_THREAD_SAFE_STACK_H
