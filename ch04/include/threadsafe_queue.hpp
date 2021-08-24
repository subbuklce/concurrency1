#pragma once
#include "headers.h"

template <class T>
class threadsafe_queue{
    public:
        T& front(){
            std::lock_guard<std::mutex> lg(mtx);
            if(mqueue.empty())
                return T();
            return mqueue.front();

        }
        T& rear(){
            std::lock_guard<std::mutex> lg(mtx);
            if(mqueue.empty())
                return T();
            return mqueue.rear();
        }
        /*
        std::shared_ptr<T> rear(){
            std::lock_guard<std::mutex> lg(mtx);
            if(mqueue.empty())
                return T();
            return make_shared<T>(mqueue.rear());
        }
        */
        void Pop(){
            std::lock_guard<std::mutex> lg(mtx);
            if(!mqueue.empty())
                mqueue.pop();
        }
        void Push(const T& val){
            std::lock_guard<std::mutex> lg(mtx);
            mqueue.push(val);
            mcv.notify_one();
            //mcv.notify_all();      
        }
        void wait_and_pop(){
            while(1){
                std::unique_lock<std::mutex> ul(mtx);
                std::cout<<"\n size of queue::"<<mqueue.size();     //not a good idea though.
                mcv.wait(ul, [this]{ return !mqueue.empty();});            
                auto v = mqueue.front();
                mqueue.pop();
                print(v);
                
         }
        }
        void print(const T& val){
            std::cout<<"\n The value is::"<<val;
        }
        bool empty(){
            std::lock_guard<std::mutex> lg(mtx);
            return mqueue.empty();
        }
private:
    std::queue<T> mqueue;
    std::condition_variable mcv;
    std::mutex mtx;
};

threadsafe_queue<int> Queue;        //Global Object


void thread_push(){
    for(auto &i:{1,2,3,4,5,5,6,7,7,8,8,8,9,10,12,13,14,14,15,15,16}){
        Queue.Push(i);
        std::this_thread::sleep_for(1000ms);
    }
}

void thread_Process_data(){
        Queue.wait_and_pop();
}

void threadsafe_main(){
    std::thread t1 = std::thread(thread_push);
    std::thread t2 = std::thread(thread_Process_data);
    scope_guard sg1(std::move(t1));
    scope_guard sg2(std::move(t2));
    
    std::cout<<"\n Starting threadsafe_main Ended..."   ;
}