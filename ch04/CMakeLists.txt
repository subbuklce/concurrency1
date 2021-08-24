cmake_minimum_required(VERSION 3.16)
project(ch04 VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)


add_executable(ch04 main.cpp include/headers.h 
                )


target_link_libraries(ch04 pthread)