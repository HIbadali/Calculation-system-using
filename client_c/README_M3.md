# TASK 3: C TCP CLIENT IMPLEMENTATION


## 🎯 PROJECT OVERVIEW

### **The Task**
Create a C program that connects to a calculation server, sends math problems, and displays the results. The server runs on port 5000 and expects a specific format for messages.

### **My Role**
I was responsible for building the C client that communicates with the server using TCP sockets.

---

## 🛠️ WHAT I BUILT

I created a **C program** (`client_c.exe`) that:

1. **Connects** to the calculation server on port 5000
2. **Asks the user** for two numbers and an operator (+, -, *, /)
3. **Formats the request** in the exact format the server expects
4. **Sends the request** over TCP connection
5. **Receives and displays** the calculation result from the server
6. **Handles errors** like timeouts, wrong inputs, and connection issues

---

## 🔍 THE PROBLEM I SOLVED

### **The Challenge**
When I first tested my client, it connected to the server but always got this error:
```
Timeout: Server did not respond
```

Even though:
- ✅ Server was running
- ✅ Client connected successfully  
- ✅ Server received the data
- ❌ But no response came back

### **My Investigation**
I discovered a **protocol mismatch**:

1. **Java client** (which worked perfectly) was sending: `NUMBER:10\r\n`
2. **My C client** was sending: `NUMBER:10\n`
3. The **difference**: Java uses `\r\n` (Windows line endings), I was using `\n` (Unix line endings)
4. The **server** was programmed to expect `\r\n`

### **The Solution**
I fixed one line in my code:

**Before (didn't work):**
```c
sprintf(request, "NUMBER:%s\nNUMBER:%s\nOPERATOR:%s\n", num1, num2, op);
```

**After (works perfectly):**
```c
sprintf(request, "NUMBER:%s\r\nNUMBER:%s\r\nOPERATOR:%s\r\n", num1, num2, op);
```

That tiny change (`\n` → `\r\n`) made everything work!

---

## ⚙️ HOW IT WORKS

### **Step-by-Step Flow**

```
[User starts client_c.exe]
      ↓
[Program initializes network connection]
      ↓
[Connects to server at 127.0.0.1:5000]
      ↓
[Asks user: "First number: "]
[Asks user: "Second number: "]
[Asks user: "Operator (+, -, *, /): "]
      ↓
[Builds message with \r\n line endings]
      ↓
[Sends: "NUMBER:100\r\nNUMBER:50\r\nOPERATOR:+\r\n"]
      ↓
[Waits for server response (5 second timeout)]
      ↓
[Receives: "RESULT:150.000000\n"]
      ↓
[Displays: "✓ Server response: RESULT:150.000000"]
      ↓
[Cleans up and exits]
```

### **Key Features in My Code**

1. **Error Checking**: If you type letters instead of numbers, it tells you
2. **Timeout Handling**: If server doesn't respond in 5 seconds, it tells you
3. **Debug Mode**: Shows exactly what's being sent (useful for testing)
4. **Clean Code**: Properly closes connections and cleans up memory

---

## 🧪 TESTING PROCESS

### **Test 1: Basic Connection**
```bash
# Started server
calc_server.exe
# Output: "Server listening on port 5000..."

# Ran my client
client_c.exe
# Entered: 100, 50, +
# Result: ✓ Got "RESULT:150.000000"
```

### **Test 2: Different Operations**
- 10 + 5 → ✓ Got 15.000000
- 20 - 8 → ✓ Got 12.000000  
- 6 * 7 → ✓ Got 42.000000
- 15 / 3 → ✓ Got 5.000000

### **Test 3: Error Cases**
- Divided by zero → ✓ Got "ERROR:Division by zero"
- Wrong operator → ✓ Got "ERROR:Invalid operator"
- Server not running → ✓ Got "Connection failed"
- Wrong input (letters) → ✓ Got "Invalid input"

### **Test 4: Protocol Verification**
My debug mode shows the exact bytes being sent:
```
Hex dump:
4E 55 4D 42 45 52 3A 31 30 30 0D 0A [CR][LF]
4E 55 4D 42 45 52 3A 35 30 0D 0A [CR][LF]  
4F 50 45 52 41 54 4F 52 3A 2B 0D 0A [CR][LF]
```
The `0D 0A` proves I'm sending the correct Windows line endings.

---

## 📁 FILES INCLUDED

Here's what I'm submitting for Task 3:

| File | Purpose |
|------|---------|
| `client_c.c` | The complete C source code |
| `client_c.exe` | Compiled program (ready to run) |
| `compile.bat` | One-click compilation script |
| `README_M3.md` | This documentation file |
| `test_results.txt` | Logs proving everything works |

---

## 🚀 HOW TO RUN IT

### **Option 1: Quick Test (Use my compiled version)**
```bash
# 1. Open two Command Prompt windows

# Window 1 - Start server:
cd "Calculation_engine\java server"
calc_server.exe

# Window 2 - Run my client:
cd client_c
client_c.exe

# 3. Enter numbers and operator when asked
```

### **Option 2: Compile and Run Yourself**
```bash
# 1. Compile the code
compile.bat
# Or: gcc client_c.c -o client_c.exe -lws2_32

# 2. Run as above
```

### **What You'll See**

**Server Window:**
```
Server listening on port 5000...
New client accepted.
[SERVER RAW RECEIVED] NUMBER:100...
[SERVER SENT] RESULT:150.000000
```

**Client Window:**
```
[✓] Connected to server
First number: 100
Second number: 50
Operator (+, -, *, /): +

✓ Server response: RESULT:150.000000
```

---

## 💡 WHAT I LEARNED

1. **Protocols Matter**: Tiny details like `\r\n` vs `\n` can break everything
2. **Debugging Skills**: How to use hex dumps to see exactly what's being sent
3. **Network Programming**: How TCP sockets work in C
4. **Cross-Language Issues**: Java and C handle things differently
5. **Error Handling**: How to make programs robust against failures

---

## ✅ TASK COMPLETION CHECKLIST

- [x] **TCP Connection**: Connects to server on port 5000
- [x] **Protocol Compliance**: Sends correct `NUMBER:`/`OPERATOR:` format
- [x] **User Interface**: Accepts input and displays results
- [x] **Error Handling**: Timeouts, invalid input, connection errors
- [x] **Testing**: Works with all operations and error cases
- [x] **Documentation**: This complete README file
- [x] **Code Quality**: Clean, commented, well-structured code

---

## 🎉 CONCLUSION

I successfully completed Task 3 by building a fully functional C TCP client for the calculation system. After solving the protocol issue, my client now:

✅ Connects reliably to the server  
✅ Sends properly formatted calculation requests  
✅ Receives and displays results  
✅ Handles all error cases gracefully  
✅ Works exactly like the Java reference client  

**My work is complete, tested, and ready for evaluation.**
```