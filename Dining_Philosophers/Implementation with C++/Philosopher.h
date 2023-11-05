// Class representing a philosopher in the dining philosophers problem.


#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H
#include "Fork.h"

class Philosopher {
public:
    int id;
    Fork* left_fork;
    Fork* right_fork;

    Philosopher(int id, Fork* left_fork, Fork* right_fork);

    void eat();
    void think();
    void dine();
};

#endif 