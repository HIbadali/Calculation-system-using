import java.io.*;
import java.net.*;
import java.util.Scanner;

public class JavaClient {
    public static void main(String[] args) {
        String hostname = "127.0.0.1";
        // Ensure this matches the C server port (5000) or Java Server port (likely 12345 later)
        int port = 5000; 

        Scanner userIn = new Scanner(System.in);
        System.out.println("--- Java Client (Robust Reconnecting Mode) ---");

        while (true) {
            System.out.println("\n--- New Calculation (Type 'exit' to quit) ---");
            
            // 1. Get User Input first
            System.out.print("Enter Number 1: ");
            String n1 = userIn.nextLine();
            if ("exit".equalsIgnoreCase(n1)) break;

            System.out.print("Enter Number 2: ");
            String n2 = userIn.nextLine();

            System.out.print("Enter Operator (+ - * /): ");
            String op = userIn.nextLine();

            // 2. Open a NEW connection for this specific calculation
            // This satisfies the requirement to handle disconnections/network flow
            try (Socket socket = new Socket(hostname, port);
                 PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                 BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()))) {

                System.out.println("[Client] Connected to server...");

                // 3. Send Data following strict Protocol
                out.println("NUMBER : " + n1);
                out.println("NUMBER : " + n2);
                out.println("OPERATOR : " + op);

                // 4. Receive Result
                String response = in.readLine();
                
                if (response != null) {
                    System.out.println("[Server Response] " + response);
                } else {
                    System.out.println("[Error] Server closed connection without replying.");
                }

            } catch (ConnectException e) {
                System.out.println("[Error] Server is not running. Please start the server.");
            } catch (IOException e) {
                System.out.println("[Network Error] " + e.getMessage());
            }
            // The socket auto-closes here, ready for the next loop.
        }
        userIn.close();
    }
}