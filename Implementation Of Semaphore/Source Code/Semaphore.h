/**
 * This class represents a semaphore with a specified count. It provides
 * methods to wait for the semaphore and signal it for other threads to proceed.
 **/


#pragma once
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>

class Semaphore {
public:
    Semaphore(int count = 1);
    void Wait();
    void Signal();
    void Signal(int count);

private:
    int count_;
    std::mutex mutex_;
    std::condition_variable condition_;
    std::queue<std::thread::id> waiting_queue_;
};