cmake_minimum_required(VERSION 3.17)
project(ch02)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
#lamda_examples.h
add_executable(ch02 main.cpp )

target_link_libraries(ch02 pthread)