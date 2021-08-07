#include "list3.2_passingout_reference.h"
#include "listing3.4_thread_safe_stack.h"
#include "deadlock_free_mutex.h"

int main() {
    list32_main_function();
    std::cout<<"\n listing 3.4 main function";
    list_3_4_main_function();
    
    std::cout<<"\n dead_lock_free_main_function";
    dead_lock_free_main_function();
    return 0;

}
