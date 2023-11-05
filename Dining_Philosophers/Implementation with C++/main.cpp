/**
 * This program simulates the dining philosophers problem.
 * The main function creates a specified number of philosophers and forks.
 * Each philosopher is assigned an ID starting from 1 and is provided with two forks.
 * Threads are created for each philosopher and they start dining.
 * After all the philosopher threads have finished their dining, the forks are cleaned up. 
 **/


#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include "Philosopher.h"

int main() {
    int philosopher_count;
    std::cout << "Enter the number of philosophers: ";
    std::cin >> philosopher_count;
    int fork_count = philosopher_count;

    // Create forks
    std::vector<Fork*> forks;
    for (int i = 0; i < fork_count; i++) {
        forks.emplace_back(new Fork(i));
    }

    // Create philosophers with IDs starting from 1
    std::vector<Philosopher> philosophers;
    for (int i = 0; i < philosopher_count; i++) {
        philosophers.emplace_back(i + 1, forks[i], forks[(i + 1) % fork_count]);
    }
    // Create threads for each philosopher
    std::vector<std::thread> threads;
    for (auto& philosopher : philosophers) {
        threads.emplace_back(&Philosopher::dine, &philosopher);
    }

    // Start threads
    for (auto& thread : threads) {
        thread.join();
    }
    // Clean up forks
    for (auto fork : forks) {
        delete fork;
    }
    return 0;
}