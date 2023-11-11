// Executive part of the program


#include "ReaderWriter.h"
#include <iostream>

void banner() {
    std::cout << R"(
#################################################################################################
#                      **  Reader-Writer Problem Simulation  **                                #
#                                                                                               #
#  This program simulates the Reader-Writer problem using threads and locks.                    #
#  It creates a specified number of readers and writers.                                        #
#  Readers can access the shared resource simultaneously, but writers require exclusive access  #
#  to the resource.                                                                             #
#                                                                                               #
#  Usage:                                                                                       #
#  1. Enter the number of readers.                                                              #
#  2. Enter the number of writers.                                                              #
#  3. The program will run and show the actions performed by each reader and writer.            #
#                                                                                               #
#################################################################################################
)" << std::endl;
}

int main() {
    banner();

    int reader_count, writer_count;
    std::cout << "---> Enter the number of readers: ";
    std::cin >> reader_count;
    std::cout << "---> Enter the number of writers: ";
    std::cin >> writer_count;

    ReaderWriter readerWriter;
    readerWriter.simulateReadersWriters(reader_count, writer_count);

    return 0;
}