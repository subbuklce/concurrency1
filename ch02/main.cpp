
#include "lamda_examples.h"
#include "list2_3_RAII.h"
#include "reference_parameters_to_thread.h"

bool do_something(){
    std::cout<<"\n This function does something ::";
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::thread t1(do_something);
    t1.join();
    std::cout<<"\n lamda expression which gets called automatically if () present at last";
    []{ do_something();}();   // This will be tread as a normal function call only.
    std::cout<<"\n The lamda function does not get called now";
    auto l = [](){do_something();};

    //lamda expression 1
    std::cout<<"\n lamda expression1 ::"<<lamda1("Hello world");

    //lamda expression2
    auto fobj1 = make_offset(12);
    auto fobj2 = make_offset(25);
    std::cout<<"\n get the value of fobj1::"<<fobj1(10) <<"\t fobj2::"<< fobj2(10);

    //
    list2_main_function();
    //
    reference_main_function();
    return 0;
}
