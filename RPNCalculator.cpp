//##################################################
// File: RPNCalculator.cpp
// Description: Initializes an empty RPN calculator.
// Date: Nov,10 2024
//##################################################



#include "RPNCalculator.h"

/**
 * @brief Custom function to convert a C-string to a double.
 * @param str The input C-string representing a numeric value.
 * @param success A reference to a boolean variable to indicate success or failure.
 * @return The converted double value, or 0.0 if the conversion fails.
 */
double stringToDouble(const char* str, bool& success) {
    double result = 0.0;
    bool isNegative = false;
    success = true;
    int i = 0;
    double decimalPlace = 0.1;

    // Check for a negative sign at the beginning
    if (str[i] == '-') {
        isNegative = true;
        i++;
    }

    // Process integer part
    while (str[i] != '\0' && str[i] != '.') {
        if (str[i] < '0' || str[i] > '9') {
            success = false;
            return 0.0;
        }
        result = result * 10 + (str[i] - '0');
        i++;
    }

    // Process decimal part if any
    if (str[i] == '.') {
        i++;
        while (str[i] != '\0') {
            if (str[i] < '0' || str[i] > '9') {
                success = false;
                return 0.0;
            }
            result += (str[i] - '0') * decimalPlace;
            decimalPlace *= 0.1;
            i++;
        }
    }

    return isNegative ? -result : result;
}

/**
 * @brief Constructor for RPNCalculator.
 */
RPNCalculator::RPNCalculator() {}

/**
 * @brief Evaluates an RPN expression and returns the result.
 * @param expression The RPN expression to evaluate, e.g., "3 2 5 * +".
 * @param errorCode Error code (0 for success, non-zero for errors).
 *        1 - Insufficient operands
 *        2 - Too many operands
 *        3 - Division by zero
 * @return The result of the evaluation, or 0 in case of error.
 * @note Manually parses tokens without any standard library functions.
 */
double RPNCalculator::evaluate(const char* expression, int& errorCode) {
    errorCode = 0;
    const char* ptr = expression;

    // Temporary buffer to store each token
    char token[32];
    int tokenIndex = 0;

    while (*ptr != '\0') {
        // Skip whitespace
        if (*ptr == ' ') {
            if (tokenIndex > 0) {
                token[tokenIndex] = '\0';
                parseAndEvaluateToken(token, errorCode);
                if (errorCode != 0) return 0.0; // Early exit on error
                tokenIndex = 0; // Reset token
            }
        } else {
            // Collect characters into the token buffer
            if (tokenIndex < 31) {
                token[tokenIndex++] = *ptr;
            }
        }
        ptr++;
    }

    // Evaluate the last token if any
    if (tokenIndex > 0) {
        token[tokenIndex] = '\0';
        parseAndEvaluateToken(token, errorCode);
        if (errorCode != 0) return 0.0;
    }

    // The final result should be the only item left in the stack
    if (stack.isEmpty()) {
        errorCode = 1; // No result (insufficient operands)
        return 0.0;
    }

    double result = stack.peek();
    stack.pop();

    // If stack is not empty, there were too many operands
    if (!stack.isEmpty()) {
        errorCode = 2;
        return 0.0;
    }

    return result;
}

/**
 * @brief Parses and evaluates a single token, either an operator or a number.
 * @param token The token to parse and evaluate.
 * @param errorCode Error code (0 for success, non-zero for errors).
 *        1 - Insufficient operands
 *        3 - Division by zero
 * @note This function uses `stringToDouble` to convert tokens to numbers and performs basic arithmetic operations.
 */
void RPNCalculator::parseAndEvaluateToken(const char* token, int& errorCode) {
    bool success = false;
    double num = stringToDouble(token, success);

    if (success) {
        // Token is a valid number, push to stack
        stack.push(num);
    } else {
        // Token is not a number, assume it's an operator
        if (stack.isEmpty()) {
            errorCode = 1; // Insufficient operands
            return;
        }
        double operand2 = stack.peek();
        stack.pop();

        if (stack.isEmpty()) {
            errorCode = 1; // Insufficient operands
            return;
        }
        double operand1 = stack.peek();
        stack.pop();

        double result = 0.0;
        if (*token == '+') result = operand1 + operand2;
        else if (*token == '-') result = operand1 - operand2;
        else if (*token == '*') result = operand1 * operand2;
        else if (*token == '/') {
            if (operand2 == 0) {
                errorCode = 3; // Division by zero
                return;
            }
            result = operand1 / operand2;
        } else {
            errorCode = 1; // Invalid token
            return;
        }

        // Push the result back onto the stack
        stack.push(result);
    }
}
