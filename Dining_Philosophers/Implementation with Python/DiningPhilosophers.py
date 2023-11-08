# This program simulates the dining philosophers problem using threads and locks.


import threading
import time

class Fork:
    def __init__(self, id):
        self.id = id
        self.lock = threading.Lock()

    def pick_up(self):
        self.lock.acquire()

    def put_down(self):
        self.lock.release()
 
class Philosopher:
    def __init__(self, id, left_fork, right_fork):
        self.id = id
        self.left_fork = left_fork
        self.right_fork = right_fork

    def eat(self):
        print(f"Philosopher {self.id} is eating.")
        time.sleep(1)               # Simulating eating

    def think(self):
        print(f"Philosopher {self.id} is thinking.")
        time.sleep(1)
 