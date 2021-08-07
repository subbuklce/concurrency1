cmake_minimum_required(VERSION 3.16)
project(ch03 VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)


add_executable(ch03 main.cpp include/headers.h 
                include/list3.2_passingout_reference.h 
                include/listing3.4_thread_safe_stack.h 
                include/listing3.5_swap_lock.h)