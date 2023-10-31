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
 

# Display output

def banner():
    print("""
          
################################################################################################################################
#                                       Producer-Consumer Multithreading                                                       #
#                                                                                                                              #  
#                   This program demonstrates the Producer-Consumer problem using multithreading.                              #
#                 It simulates a scenario where multiple producers produce items and put them into                             #
#                   a shared buffer, and multiple consumers consume those items from the buffer.                               #
#                                                                                                                              #
#       Usage:                                                                                                                 #
#           1. Enter the buffer capacity, number of producers, number of consumers, and item count per producer/consumer.      #
#           2. The program will start running and show the item production and consumption process.                            #
#           3. Once all producers have finished producing the specified number of items, and all consumers                     #
#              have consumed all the produced items, the program will terminate.                                               #
################################################################################################################################
    """)

def main():
    banner()
    bufferCapacity = int(input("Enter buffer capacity: "))
    producerCount = int(input("Enter number of producers: "))
    consumerCount = int(input("Enter number of consumers: "))
    itemCount = int(input("Enter item count per producer/consumer: "))
    buffer = Buffer(bufferCapacity)
    
    producers = []
    for i in range(1, producerCount+1):
        producers.append(threading.Thread(target=buffer.produce, args=(i, itemCount)))
    consumers = []
    for i in range(1, consumerCount+1):
        consumers.append(threading.Thread(target=buffer.consume, args=(i, itemCount, buffer, producers)))
    for producerThread in producers:
        producerThread.start()
    for consumerThread in consumers:
        consumerThread.start()
    for producerThread in producers:
        producerThread.join()
    for consumerThread in consumers:
        consumerThread.join()

if __name__ == "__main__":
    main()