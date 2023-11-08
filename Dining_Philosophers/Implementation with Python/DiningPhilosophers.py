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
 


# Display Output

def banner():
    print("""
          
###########################################################################################
#                           Dining Philosophers Problem                                   #
#                                                                                         #
#   This program simulates the Dining Philosophers problem using threads and locks.       #
#   It creates a specified number of philosophers and forks. Each philosopher goes        #
#   through a cycle of thinking, picking up the left and right forks, eating, and         #
#   putting down the forks. This process is repeated a specified number of times.         #
#                                                                                         #
#   Usage:                                                                                #
#   1. Enter the number of philosophers.                                                  #
#   2. The program will run and show the actions performed by each philosopher.           #
#                                                                                         #
###########################################################################################          
    """)

def main():
    banner()
    philosopher_count = int(input("Enter the number of philosophers: "))
    fork_count = philosopher_count
    forks = [Fork(i) for i in range(fork_count)]

    # Create philosophers with IDs starting from 1
    philosophers = [
        Philosopher(i + 1, forks[i], forks[(i + 1) % fork_count]) for i in range(philosopher_count)
    ]
    # Create threads for each philosopher
    threads = [
        threading.Thread(target=philosopher.dine) for philosopher in philosophers
    ]

    # Start threads
    for thread in threads:
        thread.start()
    # Wait for threads to finish
    for thread in threads:
        thread.join()


if __name__ == "__main__":
    main()