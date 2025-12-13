# Module: Logging, Client & Integration 
 Logging & Multithreading Support
**Additional Contribution:** Java-to-C Integration Bridge

##  Overview
This module implements the critical infrastructure for the Distributed Calculation System. It provides the **Logging Mechanism** to record server activity, the **Java Client** for user interaction, and a **Bridge Server** to link the Java environment with the C Calculation Engine.


## 1. Logging System (`LogManager.java`)
A centralized, thread-safe utility designed to capture all system operations.

### Key Technical Features
*   **Singleton Pattern:** Ensures a single logging instance manages file access across the entire application.
*   **Thread Safety (`synchronized`):** Prevents race conditions when multiple clients request calculations simultaneously. Logs are written sequentially.
*   **Persistence:** Transactions are appended to `server_log.txt` with precise timestamps.

**Log Format:**
text
[YYYY-MM-DD HH:mm:ss] [IP_ADDRESS] [STATUS] Request: {...} | Result: {...}


 How to Run the Full System
To verify the complete distributed system (Math + Logging) open 3 terminals:
Terminal 1: C Calculation Engine
code
Powershell
cd Calculation_engine
.\calc_server.exe
# (Listens on Port 5000)
Terminal 2: Java Bridge & Logger
code
Powershell
cd Java_Modules
javac Server.java LogManager.java
java Server
# (Listens on Port 6000, Links to Port 5000)
Terminal 3: Java Client
code
Powershell
cd Java_Modules
javac JavaClient.java
java JavaClient
# (Connects to Port 6000)
Verification:
After running calculations, check the Java_Modules folder for server_log.txt to see the recorded history.