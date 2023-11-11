 /**
  * This program implements a Reader-Writer synchronization solution using locks. 
  * It provides concurrent access to a shared resource: 'data'. 
  * Multiple readers can read the data simultaneously, while writers acquire an exclusive lock to modify the data.
  **/



#ifndef READERWRITER_H
#define READERWRITER_H
#include <string>
#include <mutex>
#include <vector>

class ReaderWriter {
private:
    std::string data;
    int readers_count;
    std::mutex writer_mutex;
    std::mutex reader_mutex;

public:
    ReaderWriter();
    void readData(int reader_id);
    void writeData(int writer_id);
    void startReading(int reader_id);
    void startWriting(int writer_id);
    void simulateReadersWriters(int reader_count, int writer_count);
};

#endif