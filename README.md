# This branch contains course examples of concurrency in action First edition
major utilities:
----------------------------------------------------------------------------
1. scope_guard
2. std::mem_fn()
3. std::accumulate(), std::count()
4. std::min(), std::max()
5. std::advance(), std::distance()

threads
----------------------------------------------------------------------------
std::thread::id => get_id() 
std::thread_local - independent to thread only
std::lock(lock1, lock2) - multiple locks in a single statement
std::lock_guard<std::mutex> lg - To care of mutex with RAII - Resource Aquisition Is Initialization
std::adopt_lock - Transfer the ownership to other variable only
std::defer_lock - can use unique_lock at initialization
std::unique_lock - owns_lock(), intention is to transfer the owndership of lock in between various instances.
std::call_once(std::init_once, &x::function_name, object)

