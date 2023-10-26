/**
 * The Semaphore class provides a synchronization mechanism to control access to a shared resource.
 **/

 

#include "Semaphore.h"

Semaphore::Semaphore(int count) : count_(count) {}

void Semaphore::Wait() {
    std::unique_lock<std::mutex> lock(mutex_);

    // If the count is zero, add the current thread to the waiting queue and wait until signaled.
    if (count_ == 0) {  
        waiting_queue_.push(std::this_thread::get_id());
        condition_.wait(lock, [this] {
            return !waiting_queue_.empty() && waiting_queue_.front() == std::this_thread::get_id();
        });
    }
    count_--;       // Decrement the count to acquire the resource.
}

void Semaphore::Signal() {
    std::lock_guard<std::mutex> lock(mutex_);
    count_++;       // Increment the count.

    // If there are threads waiting, notify one of them.
    if (!waiting_queue_.empty()) {  
        std::thread::id id = waiting_queue_.front();
        waiting_queue_.pop();
        condition_.notify_all();
    }
}

void Semaphore::Signal(int count) {
    std::lock_guard<std::mutex> lock(mutex_);
    count_ += count;       // Increase the count by the specified amount.

    // Notify waiting threads up to the specified count.
    while (!waiting_queue_.empty() && count > 0) {  
        std::thread::id id = waiting_queue_.front();
        waiting_queue_.pop();
        condition_.notify_all();
        count--;
    }
}