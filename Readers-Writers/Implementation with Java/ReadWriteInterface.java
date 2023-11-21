/**
 * This interface represents a Read-Write interface for handling concurrent reader and writer operations.
 * It declares methods for reading and writing data, as well as starting reading and writing tasks.
 **/


public interface ReadWriteInterface {
    void readData(int readerId);
    void writeData(int writerId);
    void startReading(int readerId);
    void startWriting(int writerId);
}
