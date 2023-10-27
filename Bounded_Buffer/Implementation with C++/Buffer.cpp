/**
 * This code demonstrates a producer-consumer pattern using a buffer. 
 * Producers produce items and add them to the buffer, while consumers
 * consume items from the buffer. The buffer acts as a shared resource
 * between the producers and consumers, with capacity limiting the number
 * of items that can be stored in the buffer at a given time. 
 **/



#include "Buffer.h"
#include <iostream>
#include <thread>

// Initializes the capacity of the buffer.
Buffer::Buffer(int capacity) : capacity(capacity) {}

void Buffer::produce(int producerID, int itemCount) {
    for (int i = 0; i < itemCount; ++i) {
        int item = i + 1;
        std::unique_lock<std::mutex> lock(mtx);
        bufferEmpty.wait(lock, [this]() { return buffer.size() < capacity; });
        buffer.push(item);
        std::cout << "Producer " << producerID << " produced item: " << item << std::endl;
        bufferFull.notify_all();
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));            // Adds a delay to simulate a slower production process.
    }
}
  
void Buffer::consume(int consumerID, int itemCount) {
    for (int i = 0; i < itemCount; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        bufferFull.wait(lock, [this]() { return !buffer.empty(); });
        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumer " << consumerID << " consumed item: " << item << std::endl;
        bufferEmpty.notify_all();
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));            // Adds a delay to simulate a slower production process.
    }
}