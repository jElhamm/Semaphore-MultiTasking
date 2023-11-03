/**
 * This class represents the main application for the Producer-Consumer problem.
 * It allows the user to specify the buffer capacity, number of producers, number of consumers,
 * and item count per producer/consumer. It creates producer and consumer threads
 * that interact with the shared buffer to produce and consume items accordingly.
 **/



import java.util.Scanner;

public class ProducerConsumer {
    public static void main(String[] args) throws InterruptedException {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter buffer capacity: ");
        final int bufferCapacity = scanner.nextInt();
        System.out.print("Enter number of producers: ");
        final int producerCount = scanner.nextInt();
        System.out.print("Enter number of consumers: ");
        final int consumerCount = scanner.nextInt();
        System.out.print("Enter item count per producer/consumer: ");
        final int itemCount = scanner.nextInt();
        scanner.close();

        final Buffer buffer = new Buffer(bufferCapacity);
        final Thread[] producers = new Thread[producerCount];
        final Thread[] consumers = new Thread[consumerCount];

        // ***************************************************************************************
        // Producer Runnable
        Runnable producerRunnable = new Runnable() {
            @Override
            public void run() {
                try {
                    for (int i = 0; i < itemCount; i++) {
                        buffer.produce(Thread.currentThread().getId(), itemCount);
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };
        // Create and start producer threads
        for (int i = 0; i < producerCount; i++) {
            producers[i] = new Thread(producerRunnable);
            producers[i].start();
        }
        // ***************************************************************************************
        // Consumer Runnable
        Runnable consumerRunnable = new Runnable() {
            @Override
            public void run() {
                try {
                    for (int i = 0; i < itemCount; i++) {
                        buffer.consume(Thread.currentThread().getId(), itemCount);
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };
        // Create and start consumer threads
        for (int i = 0; i < consumerCount; i++) {
            consumers[i] = new Thread(consumerRunnable);
            consumers[i].start();
        }
        // ***************************************************************************************


        // Wait for producer threads to finish
        for (Thread producerThread : producers) {
            producerThread.join();
        }
        // Wait for consumer threads to finish
        for (Thread consumerThread : consumers) {
            consumerThread.join();
        }
    }
}