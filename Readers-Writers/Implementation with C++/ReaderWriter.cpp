/** 
 *This program demonstrates the simulation of a Reader-Writer problem.
 * It creates a ReaderWriter object that manages concurrent access to a shared resource called 'data'.
 * The program spawns multiple reader and writer threads, simulating their behavior.
 * Readers can read the current data, while writers can modify the data by writing new information.
 * The Reader-Writer implementation ensures mutual exclusion between writers and exclusive access for writers.
 * Each reader or writer thread randomly sleeps for a period of time before performing its operation.
 **/



#include "ReaderWriter.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>

ReaderWriter::ReaderWriter() : readers_count(0) {}

void ReaderWriter::readData(int reader_id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % 3000 + 1000));
    std::cout << "** Reader " << reader_id << " is reading data. " << data << std::endl;
}

void ReaderWriter::writeData(int writer_id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % 3000 + 1000));
    std::string new_data = "** New data written by Writer " + std::to_string(writer_id);
    data = new_data;
    std::cout << "** Writer " << writer_id << " has written data. " << new_data << std::endl;
}

void ReaderWriter::startReading(int reader_id) {
    reader_mutex.lock();
    if (readers_count == 0) {
        writer_mutex.lock();
    }

    readers_count++;
    reader_mutex.unlock();
    readData(reader_id);
    reader_mutex.lock();
    readers_count--;

    if (readers_count == 0) {
        writer_mutex.unlock();
    }
    reader_mutex.unlock();
}

void ReaderWriter::startWriting(int writer_id) {
    writer_mutex.lock();
    writeData(writer_id);
    writer_mutex.unlock();
}

void ReaderWriter::simulateReadersWriters(int reader_count, int writer_count) {
    ReaderWriter reader_writer;
    std::vector<std::thread> readers;
    std::vector<std::thread> writers;

    for (int i = 0; i < reader_count; i++) {
        readers.emplace_back(&ReaderWriter::startReading, &reader_writer, i + 1);
    }
    for (int i = 0; i < writer_count; i++) {
        writers.emplace_back(&ReaderWriter::startWriting, &reader_writer, i + 1);
    }
    for (std::thread& reader : readers) {
        reader.join();
    }
    for (std::thread& writer : writers) {
        writer.join();
    }
}   