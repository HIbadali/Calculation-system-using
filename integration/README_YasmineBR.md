Integration & Testing – Yasmine
Overview
I am responsible for validating the stability and correctness of the distributed calculation system under stress and ensuring full integration between the Java components and the native C calculation engine through the JNI bridge.

Deliverables
Stress Tester (integration/StressTester.java)
A multithreaded Java client that spawns 50 concurrent connections to the TCP calculation server, sending randomized requests (NUMBER:a, NUMBER:b, OPERATOR:op) and printing the server’s structured responses.

Verified correct handling of valid operations (+, -, *, /) with RESULT:<value> responses.

Verified error handling for invalid operators, invalid formats, non‑numeric values, and division by zero via ERROR:<description> responses.

Confirmed server stability under concurrent load and that all operations are logged with timestamps.

JNI Bridge (integration/CalculatorBridge.java + native engine)
A Java class that loads the native calculation library (calc_engine.dll on Windows) and delegates arithmetic operations to the C implementation.

Declares and uses the native method calculate(int a, int b, char op) which is implemented in Calculation_engine/calc_engine.c and exposed via integration_CalculatorBridge.h.

Successfully integrated with the TCP server so that all client requests are processed by the native engine instead of the previous mock function.

Test Results
Server Executable (calc_server.exe)

Successfully handled 50 concurrent requests from the StressTester, with correct routing of all calculations to the native engine.

Responses returned correctly in the terminal output and matched the results produced directly by the C engine for the same inputs.

Log file entries confirmed that each request and result/error was recorded without crashes or data corruption under stress.

Stress Tester Output

Multiple RESULT:… lines observed for valid operations, matching expected native computation results.

Proper ERROR:… messages for invalid inputs and division by zero, consistent with both the Java protocol and the native error handling.

Demonstrated robustness of the complete chain: Java client → TCP server → JNI bridge → C engine → back to client.

Completed Work
Native Integration

Replaced the initial mock JNI implementation with the final native engine (calc_engine.c) compiled into calc_engine.dll and loaded by CalculatorBridge.

Validated Java ↔ C calls through unit tests on CalculatorBridge and end‑to‑end tests using the StressTester and TCP server.

Confirmed that the integration respects the project protocol (NUMBER, OPERATOR, RESULT, ERROR) and can be reused by the web gateway defined in the project specification.

Notes
Stress testing confirms that socket‑based communication and the JNI bridge remain stable even under high concurrency.

The current implementation is ready to be plugged into the web TCP gateway so that HTTP requests from the mini web platform can transparently use the native calculation engine.

All scripts, configuration notes, and representative test logs are maintained in the repository for grading