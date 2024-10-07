// Name: Zana Osman
// Student Number: 200489300
// Date: February 26th, 2024

#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Function to check if the character is an operand
// Alphabets
bool isOperand(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

// Function to check if a character is an operator
// Variables, numbers, etc
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Function to determine the precedence of an operator
int precedence(char op) {
    // Medium precedence
    if (op == '+' || op == '-')
        return 1;
    // Highest precedence
    if (op == '*' || op == '/')
        return 2;
    // Assuming '(' has the lowest precedence
    else
        return 0; 
}

// Function to convert infix (input) expression to postfix (output) expression
string infixtopostfix(string infix) {
    // Empty to start then we append and add as function runs 
    string postfix = "";
    // stack allows us to declare s as a stack so we can store the characters
    stack<char> s;
    
    // For loop to go through the string, the char& c : infix sets a reference to c
    // for each character in infix
    for (char& c : infix) {
        // If there is a blank space it will continue and not count it
        if (isspace(c)) {
            continue;
        }

        // Checks if the current character is an operand (letter)
        // Appends to the postfix string above
        if (isOperand(c)) {
            postfix += c;
        }

        // Left bracket
        else if (c == '(') {
            s.push(c);
        } 

        // Right bracket
        else if (c == ')') { 
            // Goes through the stack and goes until stack is empty or top of stack is a '('
            // It appends each operator but not the '(' and then removes it all from the stack
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            // After the while loop, if the stack is not empty then there is a ')'
            // It will pop or 'delete' it out since we dont need it anymore
            if (!s.empty()) 
                s.pop(); 
        }

        // This while loop goes through the code and pushes operators
        // It then determines what comes first using the precedence function
        else { 
            while (!s.empty() && precedence(s.top()) >= precedence(c)) {
                postfix += s.top();
                s.pop();
            }
            // If above is not satisfied it pushes to c
            s.push(c);
        }
    }

    // Empties out the stack until s, our stack, is empty and has nothing left in it
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }

    // Returns the finished stack to postfix so it can go back to main and be printed out
    return postfix;
}

int main() {
    // Define the infix for input and postfix is our
    string infix;

    // We ask the user to enter the infix so that the code can be implemented
    // getline because its a string
    cout << "Enter the infix expression: ";
    getline(cin, infix);

    // Set the posfix (output) to be what the function gives us from the infix (input)
    // Then we print it off using the cout and complete the code
    string postfix = infixtopostfix(infix);
    cout << "The postfix expression is: " << postfix << endl;

    return 0;
}
