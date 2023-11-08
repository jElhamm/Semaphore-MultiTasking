# This program simulates the dining philosophers problem using threads and locks.


import threading

class Fork:
    def __init__(self, id):
        self.id = id
        self.lock = threading.Lock()

    def pick_up(self):
        self.lock.acquire()

    def put_down(self):
        self.lock.release()
 