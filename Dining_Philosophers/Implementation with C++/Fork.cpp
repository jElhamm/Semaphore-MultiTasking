/** 
 * Each fork is uniquely identified by an ID.
 * The Fork class provides methods to pick up and put down the fork.
 * It ensures thread-safety by using a mutex (mtx) to control access to the fork.
 * Multiple philosophers (threads) can attempt to pick up the fork concurrently, but only one can successfully acquire it at a time.
 * If a philosopher tries to pick up a fork that is currently held by another philosopher, they will block until it becomes available.
 **/


#include "Fork.h"

Fork::Fork(int id) : id(id) {}

void Fork::pick_up() {
    mtx.lock();
}

void Fork::put_down() {
    mtx.unlock();
}