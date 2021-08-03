cmake_minimum_required(VERSION 3.17)
project(ch03)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(ch03 main.cpp include/headers.h)