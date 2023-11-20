# This class simulates the Reader-Writer problem using threads and locks.
# Readers can access the shared resource simultaneously,
# but writers require exclusive access to the resource.



import threading
import time
import random

class ReaderWriter:
    def __init__(self):
        self.data = ""
        self.readers_count = 0
        self.writer_lock = threading.Lock()
        self.readers_lock = threading.Lock()

    def read_data(self, reader_id):
        time.sleep(random.randint(1, 3))
        print(f"** Reader {reader_id} is reading data. {self.data}")

    def write_data(self, writer_id):
        time.sleep(random.randint(1, 3))
        new_data = f"** New data written by Writer {writer_id}"
        self.data = new_data
        print(f"** Writer {writer_id} has written data. {new_data}")
 
    def start_reading(self, reader_id):
            self.readers_lock.acquire()
            # If first reader, acquire writer lock
            if self.readers_count == 0:
                self.writer_lock.acquire()

            self.readers_count += 1
            self.readers_lock.release()
            self.read_data(reader_id)
            self.readers_lock.acquire()
            self.readers_count -= 1

            # If last reader, release writer lock
            if self.readers_count == 0:
                self.writer_lock.release()
            self.readers_lock.release()

    def start_writing(self, writer_id):
        self.writer_lock.acquire()
        self.write_data(writer_id)
        self.writer_lock.release()
 
def simulate_readers_writers(reader_count, writer_count):
    reader_writer = ReaderWriter()
    readers = []
    writers = []

    for i in range(reader_count):
        readers.append(threading.Thread(target=reader_writer.start_reading, args=(i+1,)))
    for i in range(writer_count):
        writers.append(threading.Thread(target=reader_writer.start_writing, args=(i+1,)))

    # Starts
    for reader in readers:
        reader.start()
    for writer in writers:
        writer.start()

    # Wait for reader threads to finish
    for reader in readers:
        reader.join()
    # Wait for writer threads to finish
    for writer in writers:
        writer.join()
  


# Display Output

def banner():
    print("""
          
#################################################################################################
#                        **  Reader-Writer Problem Simulation  **                               #
#                                                                                               #
#          This program simulates the Reader-Writer problem using threads and locks.            #
#      It creates a specified number of readers and writers. Readers can access the shared      #
#         resource simultaneously, but writers require exclusive access to the resource.        #
#                                                                                               #
#         Usage:                                                                                #
#         1. Enter the number of readers.                                                       #
#         2. Enter the number of writers.                                                       #
#         3. The program will run and show the actions performed by each reader and writer.     #
#                                                                                               #
#################################################################################################          
    """)

def main():
    banner()
    reader_count = int(input("---> Enter the number of readers: "))
    writer_count = int(input("---> Enter the number of writers: "))
    simulate_readers_writers(reader_count, writer_count)


if __name__ == "__main__":
    main()