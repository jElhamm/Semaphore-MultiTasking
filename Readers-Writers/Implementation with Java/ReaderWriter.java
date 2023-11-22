/**
 * The ReaderWriter class represents a simple implementation of a reader-writer problem. 
 * It allows multiple readers to read data concurrently, while ensuring that only one writer can write data at a time, 
 * and no reader can read while there is an active writer.
 **/



import java.util.Random;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ReaderWriter implements ReadWriteInterface {
    private String data;
    private int readersCount;
    private Lock writerLock;
    private Lock readersLock;

    public ReaderWriter() {
        this.data = "";
        this.readersCount = 0;
        this.writerLock = new ReentrantLock();
        this.readersLock = new ReentrantLock();
    }
    // Rread Data Function
    public void readData(int readerId) {
        try {
            TimeUnit.MILLISECONDS.sleep(new Random().nextInt(3000) + 1000);
            System.out.println("** Reader " + readerId + " is reading data. " + this.data);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
    // Write Data Function
    public void writeData(int writerId) {
        try {
            TimeUnit.MILLISECONDS.sleep(new Random().nextInt(3000) + 1000);
            String new_data = "** New data written by Writer " + writerId;
            this.data = new_data;
            System.out.println("** Writer " + writerId + " has written data. " + new_data);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
  
}
