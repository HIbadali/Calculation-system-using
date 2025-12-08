@echo off
echo ========================================
echo Compiling C Client (Task 3 - M3)
echo ========================================
echo.

cd /d %~dp0

echo [1] Checking for GCC...
where gcc >nul 2>nul
if errorlevel 1 (
    echo [ERROR] GCC not found! Install MinGW-w64
    echo Download from: https://sourceforge.net/projects/mingw-w64/
    pause
    exit /b 1
)

echo [2] Compiling client_c.c...
gcc src/client_c.c -o client_c.exe -lws2_32 -Wall

if errorlevel 1 (
    echo [ERROR] Compilation failed!
    pause
    exit /b 1
)

echo [✓] Compilation successful!
echo [✓] Executable: client_c.exe
echo.
echo [3] To run: client_c.exe
echo.

pause