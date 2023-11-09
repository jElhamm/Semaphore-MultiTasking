package com.dining_philosophers;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class LockBasedFork implements InterfaceFork {
    private int id;
    private Lock lock;

    public LockBasedFork(int id) {
        this.id = id;
        this.lock = new ReentrantLock();
    }

    @Override
    public void pickUp() {
        lock.lock();
    }

    @Override
    public void putDown() {
        lock.unlock();
    }
}
