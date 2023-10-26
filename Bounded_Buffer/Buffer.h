/**
 * This code defines a class Buffer that represents a thread-safe buffer with a specified capacity.
 **/



#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

class Buffer {
private:
    std::queue<int> buffer;
    std::mutex mtx;
    std::condition_variable bufferEmpty, bufferFull;
    int capacity;

public:
    explicit Buffer(int capacity);
    void produce(int producerID, int itemCount);
    void consume(int consumerID, int itemCount);
};