# This code solves the classic producer-consumer problem using multithreading in Python. The program creates a shared buffer with 
# a specified capacity and spawns multiple producer and consumer threads. 
# Producers produce a specified number of items, while consumers consume these items from the buffer.



import threading
import queue
import time

class Buffer:
    def __init__(self, capacity):
        self.buffer = queue.Queue(capacity)
        self.bufferEmpty = threading.Condition()
        self.bufferFull = threading.Condition()
        self.capacity = capacity
        self.producers_finished = 0
        self.items_produced = 0

def produce(self, producerID, itemCount):
    for i in range(itemCount):
        # Acquire the lock for bufferEmpty
        with self.bufferEmpty:
            while self.buffer.full() and self.producers_finished == 0:
                self.bufferEmpty.wait()

            # If all producers have finished, exit the loop
            if self.producers_finished == 1:
                break

            item = i + 1
            self.buffer.put(item)
            self.items_produced += 1
            print(f"Producer {producerID} produced item: {item}")

            # If the buffer becomes full, notify waiting consumers
            if self.buffer.full():
                self.bufferEmpty.notify()

        time.sleep(0.5)         # Sleep for 0.5 seconds to simulate some processing time

    # Acquire the lock for bufferFull
    with self.bufferFull:
        self.producers_finished += 1
        # If all producers have finished, notify all waiting consumers
        if self.producers_finished == itemCount:
            self.bufferFull.notify_all()
 