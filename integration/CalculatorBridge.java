package integration;

public class CalculatorBridge {
    static {
        System.loadLibrary("calculator"); // loads libcalculator.so or calculator.dll
    }

    public native String calculate(int a, int b, char op);
}
