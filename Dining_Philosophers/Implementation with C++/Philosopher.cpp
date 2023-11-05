/** 
 *Represents a philosopher in the Dining Philosophers problem.
 * Each philosopher has an ID, a left fork, and a right fork.
 * The `eat` method simulates the philosopher eating for a certain duration.
 * The `think` method simulates the philosopher thinking for a certain duration.
 * The `dine` method represents the process of the philosopher eating and thinking in a loop.
 * The philosopher thinks, picks up the left and right fork, eats, and then puts down the forks.
 * This process repeats for a specified number of iterations.
 **/



#include "Philosopher.h"
#include <iostream>
#include <chrono>
#include <thread>

Philosopher::Philosopher(int id, Fork* left_fork, Fork* right_fork) : id(id), left_fork(left_fork), right_fork(right_fork) {}

void Philosopher::eat() {
    std::cout << "Philosopher " << id << " is eating." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));               // Simulating eating
}

void Philosopher::think() {
    std::cout << "Philosopher " << id << " is thinking." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));               // Simulating thinking
}

void Philosopher::dine() {
    // Each philosopher will eat 3 times
    for (int i = 0; i < 3; i++) {
        think();
        // Pick up 
        left_fork->pick_up();
        std::cout << "Philosopher " << id << " picked up left fork." << std::endl;
        right_fork->pick_up();
        std::cout << "Philosopher " << id << " picked up right fork." << std::endl;

        eat();
        // Put down
        right_fork->put_down();
        std::cout << "Philosopher " << id << " put down right fork." << std::endl;
        left_fork->put_down();
        std::cout << "Philosopher " << id << " put down left fork." << std::endl;
    }
}