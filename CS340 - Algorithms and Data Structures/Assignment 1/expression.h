#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>

using namespace std;

// Node structure for the expression tree
struct Node {
    string value;
    Node* left;
    Node* right;

    // Constructor for creating a tree node
    Node(string value);
};

// Function to check operator precedence
int precedence(char op);

// Helper function to determine if the token is an operator
bool isOperator(const string& token);

// Function to convert infix notation to postfix notation
string infixToPostfix(const string& infix);

// Function to construct an expression tree from a postfix expression
Node* postfixToExpressionTree(const string& postfix);

// Function to construct an expression tree from a prefix expression
Node* prefixToExpressionTree(const string& prefix);

// Inorder traversal (used for infix notation)
string inorderTraversal(Node* root);

// Preorder traversal (used for prefix notation)
string preorderTraversal(Node* root);

// Postorder traversal (used for postfix notation)
string postorderTraversal(Node* root);

// Function to evaluate the expression tree
double evaluateExpressionTree(Node* root);

// Function to detect the type of expression: infix, prefix, or postfix
string detectExpressionType(const string& expression);

#endif
