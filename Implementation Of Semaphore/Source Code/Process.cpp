/**
 * This class represents a process that can enter and exit a critical section,
 * using a semaphore for synchronization.
 * 
 **/


#include "Process.h"
#include <chrono>
#include <thread>

Process::Process(const std::string& name, int priority) : name_(name), priority_(priority) {}

void Process::Execute(Semaphore& semaphore) {
    std::cout << name_ << " is waiting to enter the critical section." << std::endl;
    semaphore.Wait();
    std::cout << name_ << " has entered the critical section." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << name_ << " is exiting the critical section." << std::endl;
    semaphore.Signal();
}

bool Process::operator<(const Process& other) const {
    return priority_ < other.priority_;
}