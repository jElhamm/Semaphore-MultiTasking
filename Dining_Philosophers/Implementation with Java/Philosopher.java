/**
 * Philosopher class represents a philosopher in the dining philosophers problem.
 * It implements the Runnable interface.
 * Each philosopher thinks and eats in a cyclic manner, using the left and right forks.
 **/



public class Philosopher implements Runnable {
    private int id;
    private InterfaceFork leftFork;
    private InterfaceFork rightFork;

    public Philosopher(int id, InterfaceFork leftFork, InterfaceFork rightFork) {
        this.id = id;
        this.leftFork = leftFork;
        this.rightFork = rightFork;
    }

    public void eat() {
        System.out.println("Philosopher " + id + " is eating.");
        try {
            Thread.sleep(1000); // Simulating eating
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void think() {
        System.out.println("Philosopher " + id + " is thinking.");
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        // Each philosopher will eat 3 times
        for (int i = 0; i < 3; i++) {
            think();
            // Pick up
            leftFork.pickUp();
            System.out.println("Philosopher " + id + " picked up left fork.");
            rightFork.pickUp();
            System.out.println("Philosopher " + id + " picked up right fork.");

            eat();
            // Put down
            rightFork.putDown();
            System.out.println("Philosopher " + id + " put down right fork.");
            leftFork.putDown();
            System.out.println("Philosopher " + id + " put down left fork.");
        }
    }
}
