package integration;

import java.io.*;
import java.net.*;
import java.util.Random;
import java.util.concurrent.*;

public class StressTester {
    public static void main(String[] args) throws Exception {
        ExecutorService pool = Executors.newFixedThreadPool(20);
        Random rand = new Random();

        for (int i = 0; i < 50; i++) {
            pool.execute(() -> {
                try (Socket socket = new Socket("localhost", 5000);
                     PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                     BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()))) {

                    // Randomize inputs
                    int a = rand.nextInt(100);   // random number 0–99
                    int b = rand.nextInt(100);   // random number 0–99
                    char[] ops = {'+', '-', '*', '/'};
                    char op = ops[rand.nextInt(ops.length)];

                    // Occasionally send invalid operator to test error handling
                    if (rand.nextInt(10) == 0) {
                        op = '?';
                    }

                    // Send protocol lines
                    out.println("NUMBER:" + a);
                    out.println("NUMBER:" + b);
                    out.println("OPERATOR:" + op);

                    // Read response
                    String response = in.readLine();
                    System.out.println("Request: " + a + " " + op + " " + b + " -> " + response);

                } catch (IOException e) {
                    System.err.println("Connection failed: " + e.getMessage());
                }
            });
        }

        pool.shutdown();
        pool.awaitTermination(30, TimeUnit.SECONDS);
    }
}
