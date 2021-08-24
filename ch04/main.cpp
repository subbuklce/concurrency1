#include "threadsafe_queue.hpp"
#include "listing4.7async.hpp"
#include "listing4.9packaged_task.hpp"


int main(){

    std::cout<<"\n Starting threadsafe_main start...";       
    //threadsafe_main();
    std::cout<<"\n listing4_7async_main start...";
    listing4_7async_main();
    
    std::cout<<"\n packaged_task_main start...";
    packaged_task_main ();
    return 0;
}