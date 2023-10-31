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

            time.sleep(0.5)

        # Acquire the lock for bufferFull
        with self.bufferFull:
            self.producers_finished += 1
            if self.producers_finished == itemCount:
                self.bufferFull.notify_all()
 
    def consume(self, consumerID, itemCount, buffer, producers):
        for i in range(itemCount):
            with self.bufferFull:
                while self.buffer.empty() and self.producers_finished < itemCount:
                    self.bufferFull.wait()

                # Exit the loop if all producers have finished and the buffer is empty
                if self.producers_finished == itemCount and self.buffer.empty():
                    break

                item = self.buffer.get()
                print(f"Consumer {consumerID} consumed item: {item}")

                # Notify waiting producers if the buffer becomes empty
                if self.buffer.empty():
                    self.bufferFull.notify()

            time.sleep(0.5)

        with self.bufferEmpty:
            # Notify all waiting consumers if all items have been produced
            if self.items_produced == itemCount * len(producers):
                self.bufferEmpty.notify_all()
 