/* This program simulates the Reader-Writer Problem.
 * It prompts the user for the number of readers and writers, and then initiates threads for each reader and writer. 
 * The readers and writers access the shared resource using synchronization mechanisms. The program demonstrates concurrent access to shared 
 * data and helps illustrate the challenges of coordinating multiple readers and writers effectively.
 **/ 

public class App {
    public static void main(String[] args) {
        System.out.println("\n#################################################################################################");
        System.out.println("                        **  Reader-Writer Problem Simulation  **                               ");
        int readerCount = getInput(" ---> Enter the number of readers: ");
        int writerCount = getInput(" ---> Enter the number of writers: ");
        simulateReadersWriters(readerCount, writerCount);
    }

    public static void simulateReadersWriters(int readerCount, int writerCount) {
        Thread[] readers = new Thread[readerCount];
        Thread[] writers = new Thread[writerCount];

        for (int i = 0; i < readerCount; i++) {
            final int readerId = i + 1;
            readers[i] = new Thread(new Runnable() {
                @Override
                public void run() {
                    ReaderWriter readerWriter = new ReaderWriter();
                    readerWriter.startReading(readerId);
                }
            });
            readers[i].start();
        }
        for (int i = 0; i < writerCount; i++) {
            final int writerId = i + 1;
            writers[i] = new Thread(new Runnable() {
                @Override
                public void run() {
                    ReaderWriter readerWriter = new ReaderWriter();
                    readerWriter.startWriting(writerId);
                }
            });
        }
 
        try {
            for (Thread reader : readers) {
                reader.join();
            }
            for (Thread writer : writers) {
                writer.join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
    public static int getInput(String prompt) {
        System.out.print(prompt);
        return Integer.parseInt(System.console().readLine());
    }
}