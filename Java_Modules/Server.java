import java.io.*;
import java.net.*;

public class Server {
    // We listen for Clients on Port 6000
    private static final int MY_PORT = 6000;
    // We talk to the C Engine on Port 5000
    private static final int C_ENGINE_PORT = 5000; 

    public static void main(String[] args) {
        System.out.println("--- JAVA MAIN SERVER STARTED ---");
        System.out.println("1. Waiting for Clients on Port " + MY_PORT);
        System.out.println("2. Linking to C Engine on Port " + C_ENGINE_PORT);

        try (ServerSocket serverSocket = new ServerSocket(MY_PORT)) {
            while (true) {
                // Wait for a connection
                Socket clientSocket = serverSocket.accept();
                System.out.println("New Client Connected!");
                
                // Create a new thread for this client (Multi-threading requirement)
                new Thread(() -> handleClient(clientSocket)).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleClient(Socket clientSocket) {
        try (
            // Input/Output for the User (Client)
            BufferedReader clientIn = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            PrintWriter clientOut = new PrintWriter(clientSocket.getOutputStream(), true);
            
            // Input/Output for the C Engine
            Socket cSocket = new Socket("127.0.0.1", C_ENGINE_PORT);
            BufferedReader cIn = new BufferedReader(new InputStreamReader(cSocket.getInputStream()));
            PrintWriter cOut = new PrintWriter(cSocket.getOutputStream(), true)
        ) {
            // 1. Read the 3 lines from the Client
            StringBuilder fullRequest = new StringBuilder();
            for (int i = 0; i < 3; i++) {
                String line = clientIn.readLine();
                if (line == null) break;
                
                // Send to C Engine
                cOut.println(line);
                // Save for Log
                fullRequest.append(line).append(", ");
            }

            // 2. Get the Result from C Engine
            String result = cIn.readLine();
            
            // 3. LOG IT (This uses YOUR LogManager)
            LogManager.getInstance().logTransaction(
                clientSocket.getInetAddress().toString(), 
                fullRequest.toString(), 
                result, 
                false
            );
            
            System.out.println("Logged: " + fullRequest + " -> " + result);

            // 4. Send Result back to Client
            clientOut.println(result);

        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
            // Log the error
            LogManager.getInstance().logTransaction(
                clientSocket.getInetAddress().toString(), 
                "Connection Error", 
                e.getMessage(), 
                true
            );
        }
    }
}