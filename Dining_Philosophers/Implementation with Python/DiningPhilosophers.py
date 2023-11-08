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
 
    def dine(self):
        # Each philosopher will eat 3 times
        for _ in range(3):
            self.think()
            # Pick up
            self.left_fork.pick_up()
            print(f"Philosopher {self.id} picked up left fork.")
            self.right_fork.pick_up()
            print(f"Philosopher {self.id} picked up right fork.")
            
            self.eat()
            # Put down
            self.right_fork.put_down()
            print(f"Philosopher {self.id} put down right fork.")
            self.left_fork.put_down()
            print(f"Philosopher {self.id} put down left fork.")
 