/**
 * This class represents a process with a name and a priority. It provides
 * methods to execute the process and compare its priority with other processes.
 **/


#pragma once
#include <string>
#include <iostream>
#include "Semaphore.h"

class Process {
public:
    Process(const std::string& name, int priority);
    void Execute(Semaphore& semaphore);
    bool operator<(const Process& other) const;

private:
    std::string name_;
    int priority_;
};