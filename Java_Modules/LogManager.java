import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class LogManager {
    private static final String LOG_FILE = "server_log.txt"; //here logs are saved
    
    private static LogManager instance;

    private LogManager() {}

    public static synchronized LogManager getInstance() {
        if (instance == null) {
            instance = new LogManager();
        }
        return instance;
    }

    /**
     * The Logging Method
     * This puts the text into the file.
     * The word 'synchronized' is the Traffic Light!
     */
    public synchronized void logTransaction(String clientIp, String request, String result, boolean isError) {
        
        // Get the current time
        String timestamp = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
        
        String status = isError ? "ERROR" : "SUCCESS";

        String logEntry = String.format("[%s] [%s] [%s] Request: {%s} | Result: {%s}", 
                                        timestamp, clientIp, status, request, result);

        try (FileWriter fw = new FileWriter(LOG_FILE, true); // 'true' means append (add to end)
             BufferedWriter bw = new BufferedWriter(fw);
             PrintWriter out = new PrintWriter(bw)) {
            
            out.println(logEntry); // Write the line inside the file
            System.out.println("LOGGED: " + logEntry); // Show it on your screen too

        } catch (IOException e) {
            System.err.println("Could not write to log file: " + e.getMessage());
        }
    }
}