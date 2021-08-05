cmake_minimum_required(VERSION 3.17)
project(ch02)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
#lamda_examples.h
add_executable(ch02 main.cpp include/list2_3_RAII.h include/headers.h include/reference_parameters_to_thread.h include/listing_2.8.h)

target_link_libraries(ch02 pthread)