/**
 * This class represents a dining philosophers simulation.
 * It allows multiple philosophers to dine using the provided forks
 * and ensures that they follow the dining protocol to avoid deadlock.
 * The program waits for user input to stop the simulation.
 **/



import java.util.Scanner;

public class App {
    private static volatile boolean running = true; // Flag to control execution

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("****************************************************************");
        System.out.print("---> Enter the number of philosophers: ");
        int philosopherCount = scanner.nextInt();
        InterfaceFork[] forks = new InterfaceFork[philosopherCount];
        Philosopher[] philosophers = new Philosopher[philosopherCount];
        Thread[] threads = new Thread[philosopherCount];

        // Create forks
        for (int i = 0; i < forks.length; i++) {
            forks[i] = new LockBasedFork(i);
        }
        // Create philosophers
        for (int i = 0; i < philosophers.length; i++) {
            InterfaceFork leftFork = forks[i];
            InterfaceFork rightFork = forks[(i + 1) % philosopherCount];
            philosophers[i] = new Philosopher(i + 1, leftFork, rightFork);
            threads[i] = new Thread(philosophers[i]);
        }
        // Start threads
        for (Thread thread : threads) {
            thread.start();
        }
        // Wait for input to stop the program
        System.out.println("Press enter to stop the program...");
        scanner.nextLine();

        // Set running flag to false
        running = false;

        // Wait for threads to finish
        try {
            for (Thread thread : threads) {
                thread.join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        scanner.close();
    }
    // Method to check if program should continue running
    public static boolean isRunning() {
        return running;
    }
}