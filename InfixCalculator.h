//##################################################
// File: InfixCalculator.h
// Author: Anthony Williams
// Description:An infix notation calculator class that converts infix expressions to postfix and then evaluates them using the RPNCalculator.
// Date: Nov,10 2024
//##################################################



#ifndef INFIXCALCULATOR_H
#define INFIXCALCULATOR_H

#include "RPNCalculator.h"

class InfixCalculator : public RPNCalculator {
public:
    InfixCalculator(); ///< Constructor for initializing the calculator.
    
    double evaluateInfix(const char* expression, int& errorCode); ///< Evaluates an infix expression.

private:
    bool isOperator(char c); ///< Checks if a character is an operator.
    int precedence(char op); ///< Returns precedence of an operator.
    bool isLeftAssociative(char op); ///< Checks if an operator is left-associative.

    void infixToPostfix(const char* infix, char* postfix, int& errorCode); ///< Converts infix expression to postfix.
};

#endif // INFIXCALCULATOR_H
