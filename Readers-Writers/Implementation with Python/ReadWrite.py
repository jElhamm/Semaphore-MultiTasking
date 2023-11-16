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
 