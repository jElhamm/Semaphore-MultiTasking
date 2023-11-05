// Class representing a fork in the dining philosophers problem.


#ifndef FORK_H
#define FORK_H
#include <mutex>

class Fork {
public:
    int id;
    std::mutex mtx;
    Fork(int id);
    void pick_up();
    void put_down();
};

#endif