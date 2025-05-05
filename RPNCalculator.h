//##################################################
// File: RPNCalculator.h
// Description: An RPN calculator class implemented using a stack.
// Date: Nov,10 2024
//##################################################



#ifndef RPNCALCULATOR_H
#define RPNCALCULATOR_H

#include "Stack.h"

class RPNCalculator {
public:
    RPNCalculator(); ///< Constructor initializes an empty RPN calculator.
    
    double evaluate(const char* expression, int& errorCode); ///< Evaluates an RPN expression and returns the result.
    
private:
    Stack<double> stack; ///< Stack to hold operands for RPN calculations.

    void parseAndEvaluateToken(const char* token, int& errorCode); ///< Parses and evaluates a single token.
};

#endif // RPNCALCULATOR_H
