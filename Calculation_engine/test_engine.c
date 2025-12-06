#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc_engine.h"
void run_test(double n1, double n2, char op, const char* description){
    printf("-----running test: %s-----", description);
    char* return_string = calculate_rpn(n1, n2, op);
    if(return_string == NULL){
        printf("Malloc failed in calculation function\n");
        return;
    }
    printf("[OUTPUT]: %s\n", return_string);
    free(return_string);
    printf("[CLEANING] Memory freed\n");
};
int main(){
    //testing all operators
    printf("------Testing Function------\n");
    run_test(5.0, 3.0, '+', "Success: Addition (5 + 3)");
    run_test(10.0, 4.0, '-', "Success: Subtraction (10 - 4)");
    run_test(2.5, 4.0, '*', "Success: Multiplication (2.5 * 4)");
    run_test(20.0, 8.0, '/', "Success: Division (20 / 8)");
    printf("\n");
    //testing for error handling
    //testing division by zero error handling
    run_test(10.0, 0.0, '/', "ERROR: Division by Zero (10 / 0)");
    
    //testing invalid operators error handling
    run_test(1.0, 2.0, '^', "ERROR: Invalid Operator (^)");
    return 0;
}
