#include <stdio.h>
#include <string.h>
#include "calc_engine.h"
#define ALLOCATE_ERROR(msg)({\
    const char* error_message = (msg);\
    char* return_string = (char*)malloc(strlen(msg)+1);\
    if(return_string != NULL){\
        strcpy(return_string, error_message);\
    }\
    return_string;\
});
char* calculate_rpn(double num1, double num2, char operator_char){
    if(operator_char == '/' && num2 == 0.0){
        return ALLOCATE_ERROR("Error: Division by zero");
    }
    double result = 0.0;
    switch (operator_char)
    {
    case '+':
        result = num1 + num2;
        break;
    case '-':
        result = num1 - num2;
        break;
    case '*':
        result = num1 * num2;
        break;
    case '/':
        result = num1 / num2;
        break;
    default:
        return ALLOCATE_ERROR("Error: Invalid operator");
    }
    char temp_buffer[100];
    snprintf(temp_buffer, sizeof(temp_buffer), "%.10f", result);
    char* return_string = (char*)malloc(strlen(temp_buffer) + 1);
    if(return_string = NULL){
        return ALLOCATE_ERROR("Error: Memeory allocation failed");
    }
    strcpy(return_string, temp_buffer);
    return return_string;
}