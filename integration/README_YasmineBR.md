# Integration & Testing – Yasmine

## Overview
I am responsible for validating the stability and correctness of the distributed calculation system under stress, and ensuring smooth integration between Java and native C components via JNI.

## Deliverables
- **Stress Tester (integration/StressTester.java)**  
  A multithreaded Java client that spawns 50 concurrent connections to the server. Each client sends randomized requests (`NUMBER:a`, `NUMBER:b`, `OPERATOR:op`) and prints the server’s response.  
  - Verified correct handling of valid operations (+, -, *, /).  
  - Verified error handling for invalid operators and division by zero.  
  - Confirmed server stability under concurrent load.

- **JNI Bridge Stub (integration/CalculatorBridge.java)**  
  A Java class prepared to load the native library (`calculator.dll` on Windows, `libcalculator.so` on Linux).  
  - Declares the native method `calculate(int a, int b, char op)`.  
  - Pending implementation in `native/calculator.c`.

## Test Results
- **Server Executable (`server.exe`)**  
  - Successfully handled 50 concurrent requests.  
  - Responses returned correctly in terminal output.  
  - `server.log` entries confirmed with timestamps, client IPs, requests, and results/errors.  
  - No crashes or corruption observed during stress testing.

- **Stress Tester Output**  
  - Multiple `RESULT: …` lines observed for valid operations.  
  - Proper `ERROR: …` messages for invalid inputs.  
  - Demonstrated robustness under randomized inputs.

## Pending Work
- **Native Integration**  
  - Awaiting delivery of `calculator.c` implementation.  
  - Once compiled into `calculator.dll`, JNI bridge will be tested with direct Java ↔ C calls.  
  - Current bridge stub (`CalculatorBridge.java`) is ready for integration.

## Notes
- Stress testing confirms socket-based communication is stable.  
- JNI testing will be finalized once the native library is available.  
- Documentation and test logs are maintained for grading and portfolio presentation.
