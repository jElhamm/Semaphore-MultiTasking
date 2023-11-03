/**
 * The `Buffer` class represents a bounded buffer with a fixed capacity.
 * It provides methods for producers to add items to the buffer and
 * consumers to remove items from the buffer. The buffer uses a blocking
 * queue to ensure thread safety. Producers can produce items and add
 * them to the buffer, while consumers can consume items from the buffer.
 * The class also keeps track of the number of producers finished and items
 * produced to determine when all items have been produced and consumed.
 **/


 
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;


public class Buffer {
    private BlockingQueue<Integer> buffer;
    private int producersFinished;
    private int itemsProduced;

    public Buffer(int capacity) {
        this.buffer = new ArrayBlockingQueue<>(capacity);
        this.producersFinished = 0;
        this.itemsProduced = 0;
    }
 
}