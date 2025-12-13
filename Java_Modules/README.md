# 1. Java Client (`JavaClient.java`)
### Key Features
*   **Seamless Connectivity:** The Java Client establishes a persistent connection with the Calculation Server, enabling efficient communication.
*   **Protocol Adherence:** It strictly adheres to the project's defined protocol, ensuring smooth data exchange with the server. The client constructs requests and interprets responses in the expected format.
*   **Error Resilience:** The client is designed to handle potential network disruptions. It automatically re-establishes connections, ensuring continuous operation and minimizing service interruptions.
*   **User-Friendly:** The client provides an intuitive command-line interface, allowing users to easily input numbers and operators for their calculations.

### Running the Client
To get the Java Client up and running, follow these straightforward steps:

1.  Navigate to the `Java_Modules` directory using your terminal.
2.  Compile the client: `javac JavaClient.java`
3.  Execute the client: `java JavaClient`

---

## 2. Logging System (`LogManager.java`)

### Design and Implementation
The Logging System is a critical component for tracking server operations. It utilizes the Singleton design pattern to ensure a single, globally accessible logging instance. This design simplifies the logging process and guarantees that all log entries are consistently managed.

### Technical Details
*   **Thread Safety:** The core logging mechanism is made thread-safe through the use of the `synchronized` keyword. This ensures that log entries from concurrent client requests are written sequentially, preventing data corruption.
*   **File Storage:** Log entries are appended to the `server_log.txt` file, preserving a comprehensive record of all server interactions.
*   **Informative Format:** Each log entry includes essential details: a timestamp, the client's IP address, the status (success or error), the calculation request, and the result.

### Integration for Server Developers
To incorporate the Logging System into the Java Server, the following steps should be taken:

1.  Import the `LogManager` class:
    ```java
    import Java_Modules.LogManager;
    ```
2.  Utilize the `logTransaction` method within the server's processing logic:
    ```java
    LogManager.getInstance().logTransaction(
        clientIPAddress, // The client's IP
        "Number:10, Number:5, Op:+", // The request details
        "Result:15", // The result of the calculation
        false // Set to true if there was an error
    );
    ```

### Log Format Example
```text
[2023-12-11 14:00:01] [127.0.0.1] [SUCCESS] Request: {10, 5, +} | Result: {15.0}
[2023-12-11 14:00:05] [127.0.0.1] [ERROR] Request: {10, 0, /} | Result: {Division by Zero}