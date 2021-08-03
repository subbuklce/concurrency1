//
// Created by subrahmanyam on 31/07/21.
//

#ifndef CH02_LAMDA_EXAMPLES_H
#define CH02_LAMDA_EXAMPLES_H
#include "headers.h"
//lamda expression 1
// lamda expression which returns true if string contains data in it.
auto lamda1 = [](std::string_view str)->bool {
    if(!str.empty())
        return true;
    return false;


};


//lamda expression2
// copy and reference member variables
std::function<int (int)> make_offset(int offset){
    return [=](int j){ return offset+j; };   // offset is a copy, returns function object
    return [&](int j){ return offset +j; };  // offset is reference to parameter which leads to undefined behavior as variable is descoped.
}

//lamda expression 3

#endif //CH02_LAMDA_EXAMPLES_H
