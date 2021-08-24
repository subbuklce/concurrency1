#pragma once

#include <iostream>
#include <thread>
#include <memory>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <future>
#include <deque>
#include <utility>

using namespace std::chrono_literals;


class scope_guard{
    public:
        scope_guard(std::thread t_):_t_(std::move(t_)){}
        ~scope_guard(){ 
            if(_t_.joinable()) _t_.join();

        }
        scope_guard(const scope_guard&)    = delete;
        scope_guard& operator=(const scope_guard&) = delete;
    private:
        std::thread _t_;

};