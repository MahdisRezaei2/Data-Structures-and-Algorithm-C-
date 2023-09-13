#include "stack.h"
#include <iostream>
#include <string>
// need a function to check it each character in each iteration is an operator or not
bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
    {
        return true;
    }
    return false;
}
// need a function to evaluate the precedence of operations, in other words, assign some values the the operations so we can compare
// them easier in the intoPrefix function
int checkPrecedence(char oparator)
{
    switch (oparator)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}
/**
 * at the end of the intoPrefix function, we need to reverse the string to get the correct prefix, calling this function helps us to do
this reversing.
we use swaping here for reversing
*/
std::string reverseString(const std::string &st)
{
    std::string reversedStr = st;
    int first = 0;
    int last = reversedStr.length() - 1;

    while (first < last)
    {
        std::swap(reversedStr[first], reversedStr[last]);
        first++;
        last--;
    }

    return reversedStr;
}
// this function converts infix to prefix
/**
 * we make a stack of character
 * have a for loop that starts from the end of the string
 * during the for loop we need to check all the characters, if they are operand we need to check their precedence and
 * we do pop and push to the stack based on these
 * also we need to check if the stack is empty or not, for this we use the isEmpty function from our header classs
*/
std::string intoPrefix(std::string &infixExpression)
{
    std::string return_string;
    stack<char> operation;
    for (int i = infixExpression.length() - 1; i >= 0; --i)
    {
        char character = infixExpression[i];
        if (character == ')')
        {
            operation.push(character);
        }
        else if (character == '(')
        {
            while (operation.peek() != ')' && !operation.isEmpty())
            {
                return_string += operation.peek();
                operation.pop();
            }
            if (operation.peek() == ')' && !operation.isEmpty())
            {
                operation.pop();
            }
        }
        else if (isOperator(character))
        {
            while (!operation.isEmpty() && checkPrecedence(operation.peek()) >= checkPrecedence(character))
            {
                return_string += operation.peek();
                operation.pop();
            }
            operation.push(character);
        }
        else
        {
            return_string += character;
        }
    }
    while (!operation.isEmpty())
    {
        return_string += operation.peek();
        operation.pop();
    }
    return_string = reverseString(return_string);
    return return_string;
}
/**
 * in this function we convert the prefix to infix using recusrion
 * this function is called by the helper function, helper function passes index which helps us to tack and traverse easier
 * the key here is that we have 2 operands here (first and second) and at the end we concatenate there operand, infact these are each pair
 * of parantesis having expresion inside them like concatenating (A+B) and (C+D)
*/
std::string intoInfix(const std::string &prefixExpression, int &index)
{
    char chars = prefixExpression[index++];
    if (isOperator(chars))
    {
        std::string firstOperand = intoInfix(prefixExpression, index);
        std::string secondOperand = intoInfix(prefixExpression, index);

        std::string infixConverted = "(" + firstOperand + chars + secondOperand + ")";
        return infixConverted;
    }
    else
    {
        return std::string("") + chars;
    }
}
// helper function
std::string intoInfix(const std::string &prefixExpression)
{
    int index = 0;
    return intoInfix(prefixExpression, index);
}
/**
 * this function converts postinfix to infix
 * helper function calls this function, by passign an index to help us traversing in the postFixExpression string
 * similare to intoInfix, we will have two operand to concatenate (fist and second operand), bc we make pair of operations
 * for exmaple (A+D) (B+ k)
 * th difference with previous function is that, in this one the index starts from the last element in the string and move to the first
*/
std::string postIntoInfix(const std::string &postFixExpression, int &index)
{  
    // the base case
    if (index < 0)
    {
        return std::string("");
    }
    char c = postFixExpression[index];
     
    if (isOperator(c))
    {
        std::string firstOperand = postIntoInfix(postFixExpression, --index);
        std::string secondOperand = postIntoInfix(postFixExpression, --index);
        std::string infixConverted = "(" + secondOperand + c + firstOperand + ")";

        return infixConverted;
    }
    else
    {
        return std::string("") + c;
    }
}
// helper function 
std::string postIntoInfix(const std::string &postFixExpression)
{

    int index = postFixExpression.length() - 1;
    return postIntoInfix(postFixExpression, index);
}
int main()
{
   // Test cases
    std::string infixExpression = "((A+B)/t-(f*g))";
    std::string prefixExpression = "*-AB+FG";
    std::string postFixExpression = "AB+FG*+";
    std::cout << "Prefix Expression: " << intoPrefix(infixExpression) << std::endl;
    std::cout << "Infix Expression from prefix: " << intoInfix(prefixExpression) << std::endl;
    std::cout << "Infix Expression from Postfix: " << postIntoInfix(postFixExpression) << std::endl;

    return 0;
}