/**
 * The main purpose of this code is to demonstrate the usage of a Semaphore class and the Process class.
 **/



#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include "Semaphore.h"
#include "Process.h"

int main() {
    // Create a counting semaphore with an initial count of 1
    Semaphore semaphore(1);

    std::string name;
    int priority;
    std::vector<Process> processes;
    int processCount;
    std::cout << "Enter the number of processes: ";
    std::cin >> processCount;

    for (int i = 1; i <= processCount; ++i) {
        std::cout << "Enter the name for Process " << i << ": ";
        std::cin >> name;
        std::cout << "Enter the priority for Process " << i << ": ";
        std::cin >> priority;

        processes.emplace_back(name, priority);
    }
    // Sort the processes
    std::sort(processes.begin(), processes.end());


    // Create threads and execute processes
    std::vector<std::thread> threads;
    for (Process& process : processes) {
        threads.emplace_back([&semaphore, &process]() {
            process.Execute(semaphore);
        });
    }
    // Join the threads
    for (std::thread& thread : threads) {
        thread.join();
    }
    
    return 0;
}