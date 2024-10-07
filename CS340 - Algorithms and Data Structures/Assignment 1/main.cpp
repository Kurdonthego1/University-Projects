#include "expression.h"
#include <iostream>

using namespace std;

int main() {
    string expression;

    // Get the arithmetic expression from the user
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);

    // Detect the type of the input expression (infix, postfix, or prefix)
    string expressionType = detectExpressionType(expression);
    Node* expressionTree = nullptr;

    // If the input is an infix expression, convert it to postfix and build the tree
    if (expressionType == "infix") {
        string postfix = infixToPostfix(expression);
        expressionTree = postfixToExpressionTree(postfix);
    } 
    // If the input is a postfix expression, build the tree directly
    else if (expressionType == "postfix") {
        expressionTree = postfixToExpressionTree(expression);
    }
    // If the input is a prefix expression, build the tree directly
    else if (expressionType == "prefix") {
        expressionTree = prefixToExpressionTree(expression);
    }

    // If the tree couldn't be constructed, exit with an error
    if (expressionTree == nullptr) {
        cerr << "Error: Could not construct the expression tree." << endl;
        return 1;
    }

    // Print the expression in infix, prefix, and postfix forms
    cout << "Expression in Infix: " << inorderTraversal(expressionTree) << endl;
    cout << "Expression in Prefix: " << preorderTraversal(expressionTree) << endl;
    cout << "Expression in Postfix: " << postorderTraversal(expressionTree) << endl;

    // Evaluate and print the result of the expression
    cout << "Evaluation of the expression: " << evaluateExpressionTree(expressionTree) << endl;

    return 0;
}
