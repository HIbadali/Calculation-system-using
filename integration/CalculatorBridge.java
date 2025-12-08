package integration;
public class CalculatorBridge {
    // Load the native library (compiled from C)
    static {
        System.loadLibrary("calc_engine");
        // On Linux: libcalc_engine.so
        // On Windows: calc_engine.dll
        // On macOS: libcalc_engine.dylib
    }

    /**
     * Native method declaration.
     * This corresponds to the C function:
     *   char* calculate_rpn(double num1, double num2, char operator_char);
     */
    public native String calculateRPN(double num1, double num2, char operator);

    // Optional test method
    public static void main(String[] args) {
        CalculatorBridge bridge = new CalculatorBridge();
        String result = bridge.calculateRPN(5.0, 3.0, '+');
        System.out.println("RPN Result: " + result);
    }
}
