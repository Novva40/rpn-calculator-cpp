//##################################################
// File: InfixCalculator.cpp
// Author: Anthony Williams
// Description: Constructor for InfixCalculator.
// Date: Nov,10 2024
//##################################################



#include "InfixCalculator.h"

InfixCalculator::InfixCalculator() {}

/**
 * @brief Evaluates an infix expression by converting it to postfix and evaluating the postfix.
 * @param expression The infix expression to evaluate.
 * @param errorCode Error code for evaluation (0 for success).
 * @return The result of the evaluated expression.
 * @note Uses `infixToPostfix` to convert the infix expression, then calls `RPNCalculator::evaluate`.
 */
double InfixCalculator::evaluateInfix(const char* expression, int& errorCode) {
    char postfix[256];
    infixToPostfix(expression, postfix, errorCode);

    if (errorCode != 0) return 0.0; // Return on conversion error

    // Use the postfix expression with RPNCalculator's evaluate function
    return RPNCalculator::evaluate(postfix, errorCode);
}

/**
 * @brief Checks if a character is an operator.
 * @param c The character to check.
 * @return True if the character is an operator, false otherwise.
 * @note Used in infix-to-postfix conversion for precedence handling.
 */
bool InfixCalculator::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

/**
 * @brief Returns the precedence of an operator.
 * @param op The operator to check.
 * @return The precedence level (higher number means higher precedence).
 * @note Based on typical operator precedence: ^ > * / > + -
 */
int InfixCalculator::precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

/**
 * @brief Checks if an operator is left-associative.
 * @param op The operator to check.
 * @return True if the operator is left-associative, false otherwise.
 * @note All operators except '^' (exponentiation) are left-associative.
 */
bool InfixCalculator::isLeftAssociative(char op) {
    return op != '^';
}

/**
 * @brief Converts an infix expression to a postfix expression.
 * @param infix The input infix expression as a C-string.
 * @param postfix The output postfix expression as a C-string.
 * @param errorCode Error code (0 for success).
 * @note Uses the stack to manage operators and apply precedence/associativity rules.
 */
void InfixCalculator::infixToPostfix(const char* infix, char* postfix, int& errorCode) {
    Stack<char> opStack;
    int postfixIndex = 0;
    errorCode = 0;

    const char* ptr = infix;
    while (*ptr != '\0') {
        // Skip whitespace
        if (*ptr == ' ') {
            ptr++;
            continue;
        }

        // Operand: Directly add to postfix expression
        if ((*ptr >= '0' && *ptr <= '9') || *ptr == '.') {
            postfix[postfixIndex++] = *ptr;
        }
        // Left parenthesis: Push onto the stack
        else if (*ptr == '(') {
            opStack.push(*ptr);
        }
        // Right parenthesis: Pop until left parenthesis
        else if (*ptr == ')') {
            while (!opStack.isEmpty() && opStack.peek() != '(') {
                postfix[postfixIndex++] = ' ';
                postfix[postfixIndex++] = opStack.peek();
                opStack.pop();
            }
            if (opStack.isEmpty() || opStack.peek() != '(') {
                errorCode = 1; // Mismatched parentheses
                return;
            }
            opStack.pop(); // Discard the '('
        }
        // Operator: Process according to precedence and associativity
        else if (isOperator(*ptr)) {
            postfix[postfixIndex++] = ' '; // Space to separate tokens
            while (!opStack.isEmpty() && isOperator(opStack.peek())) {
                char topOp = opStack.peek();
                if ((isLeftAssociative(*ptr) && precedence(*ptr) <= precedence(topOp)) ||
                    (!isLeftAssociative(*ptr) && precedence(*ptr) < precedence(topOp))) {
                    postfix[postfixIndex++] = opStack.peek();
                    opStack.pop();
                    postfix[postfixIndex++] = ' ';
                } else {
                    break;
                }
            }
            opStack.push(*ptr);
        } else {
            errorCode = 1; // Invalid character
            return;
        }
        ptr++;
    }

    // Pop remaining operators
    while (!opStack.isEmpty()) {
        postfix[postfixIndex++] = ' ';
        if (opStack.peek() == '(') {
            errorCode = 1; // Mismatched parentheses
            return;
        }
        postfix[postfixIndex++] = opStack.peek();
        opStack.pop();
    }
    postfix[postfixIndex] = '\0'; // Null-terminate the postfix expression
}
