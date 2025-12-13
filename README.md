Overview

This project implements a distributed calculation system using TCP sockets only.
It consists of a multi-threaded TCP server and a TCP client, both written in C.

The client sends two numbers and an operator to the server.
The server processes the request and returns either the result or an error message.


🔁 Communication Protocol

Client sends three lines:

NUMBER:<value>
NUMBER:<value>
OPERATOR:+ | - | * | /


Server responses:

RESULT:<value>
ERROR:<description>

⚙️ Server Features

Handles multiple clients simultaneously (multi-threading)

Validates input format and values

Prevents invalid operations (e.g. division by zero)

Logs requests, results, and errors

🧪 Compilation (Windows – MSYS2 MinGW64)

Compile the server:

gcc calc_server.c -o calc_server.exe -lws2_32


Compile the client:

gcc client.c -o client.exe -lws2_32

▶️ Execution

Run the server:

./calc_server.exe


Run the client in another terminal:

./client.exe


Expected result:

RESULT:15.000000

🛠️ Technologies

Language: C

Network: TCP Sockets (Winsock2)

Multithreading

Platform: Windows
