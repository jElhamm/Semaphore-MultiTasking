/**
 * The purpose of this class is to simulate a buffer for a producer-consumer scenario.
 * It allows multiple producers and consumers to interact with the buffer concurrently.
 **/


#include "Buffer.h"
#include <iostream>
#include <vector>
#include <thread>

int main() {
    int bufferCapacity, producerCount, consumerCount, itemCount;
    std::cout << "Enter buffer capacity: ";
    std::cin >> bufferCapacity;
    std::cout << "Enter number of producers: ";
    std::cin >> producerCount;
    std::cout << "Enter number of consumers: ";
    std::cin >> consumerCount;
    std::cout << "Enter item count per producer/consumer: ";
    std::cin >> itemCount;
    Buffer buffer(bufferCapacity);

    std::vector<std::thread> producers;
    // Loop to create producer threads.
    for (int i = 1; i <= producerCount; ++i) {
        producers.emplace_back(&Buffer::produce, &buffer, i, itemCount);
    }

    std::vector<std::thread> consumers;
    // Loop to create consumer threads.
    for (int i = 1; i <= consumerCount; ++i) {
        consumers.emplace_back(&Buffer::consume, &buffer, i, itemCount);
    }

     // Loop to wait for producer threads to finish.
    for (auto& producerThread : producers) {
        producerThread.join();
    }
    // Loop to wait for consumer threads to finish.
    for (auto& consumerThread : consumers) {
        consumerThread.join();
    }

    return 0;
}
