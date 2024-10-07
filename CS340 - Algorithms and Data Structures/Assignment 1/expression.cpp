#include "expression.h"
#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>

using namespace std;

// Node constructor for creating a tree node
Node::Node(string value) : value(value), left(nullptr), right(nullptr) {}

// Function to check operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;  // Lowest precedence
    if (op == '*' || op == '/') return 2;  // Higher precedence
    return 0;
}

// Helper function to check if the item is an operator
bool isOperator(const string& item) {
    return item == "+" || item == "-" || item == "*" || item == "/";
}

// Infix to Postfix conversion using a stack
string infixToPostfix(const string& infix) {
    stack<char> opStack;  // Stack to hold operators and parentheses
    string postfix;  // Resulting postfix expression
    string item;  // Current item

    for (int i = 0; i < infix.length(); i++) {
        item = infix[i];

        // Skip spaces
        if (item == " ") continue;

        // If the item is a digit or part of a multi-digit number
        if (isdigit(infix[i]) || (infix[i] == '-' && isdigit(infix[i + 1]))) {
            while (i < infix.length() && (isdigit(infix[i]) || infix[i] == '-')) {
                postfix += infix[i++];
            }
            postfix += ' ';
            i--;
        }
        // If it's a left parenthesis, push it onto the stack
        else if (item == "(") {
            opStack.push('(');
        }
        // If it's a right parenthesis, pop until matching '(' is found
        else if (item == ")") {
            while (!opStack.empty() && opStack.top() != '(') {
                postfix += opStack.top();
                postfix += ' ';
                opStack.pop();
            }
            opStack.pop();  // Pop the '('
        }
        // If it's an operator, handle precedence and stack
        else {
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(item[0])) {
                postfix += opStack.top();
                postfix += ' ';
                opStack.pop();
            }
            opStack.push(item[0]);
        }
    }

    // Pop remaining operators in the stack
    while (!opStack.empty()) {
        postfix += opStack.top();
        postfix += ' ';
        opStack.pop();
    }

    return postfix;
}

// Construct an expression tree from a postfix expression
Node* postfixToExpressionTree(const string& postfix) {
    stack<Node*> treeStack;  // Stack to hold tree nodes
    string item;  // Current item

    for (int i = 0; i < postfix.length(); i++) {
        item = postfix[i];

        // Skip spaces
        if (item == " ") continue;

        // If the item is an operand (number), create a leaf node
        if (isdigit(postfix[i]) || (postfix[i] == '-' && isdigit(postfix[i + 1]))) {
            string number;
            while (i < postfix.length() && (isdigit(postfix[i]) || postfix[i] == '-')) {
                number += postfix[i++];
            }
            treeStack.push(new Node(number));
            i--;  // Adjust index after number parsing
        }
        // If the item is an operator, pop two nodes and create a new subtree
        else if (isOperator(item)) {
            if (treeStack.size() < 2) {
                cerr << "Error: Not enough operands for the operator: " << item << endl;
                return nullptr;
            }
            // Pops the right and left then creates the subtree
            Node* right = treeStack.top(); treeStack.pop();
            Node* left = treeStack.top(); treeStack.pop();
            Node* node = new Node(item);
            node->left = left;
            node->right = right;
            treeStack.push(node);
        }
    }

    // If the stack doesn't have exactly one node, it's an invalid expression
    if (treeStack.size() != 1) {
        cerr << "Error: Invalid postfix expression." << endl;
        return nullptr;
    }

    return treeStack.top();  // Root of the tree
}

// Construct an expression tree from a prefix expression
Node* prefixToExpressionTree(const string& prefix) {
    stack<Node*> treeStack;  // Stack to hold tree nodes
    string item;  // Current item

    for (int i = prefix.length() - 1; i >= 0; i--) {
        item = prefix[i];

        // Skip spaces
        if (item == " ") continue;

        // If the item is an operand (number), create a leaf node
        if (isdigit(prefix[i]) || (prefix[i] == '-' && isdigit(prefix[i - 1]))) {
            string number;
            while (i >= 0 && (isdigit(prefix[i]) || prefix[i] == '-')) {
                number = prefix[i--] + number;
            }
            treeStack.push(new Node(number));
            i++;  // Adjust index after number parsing
        }
        // If the item is an operator, pop two nodes and create a new subtree
        else if (isOperator(item)) {
            if (treeStack.size() < 2) {
                cerr << "Error: Not enough operands for the operator: " << item << endl;
                return nullptr;
            }
            Node* left = treeStack.top(); treeStack.pop();
            Node* right = treeStack.top(); treeStack.pop();
            Node* node = new Node(item);
            node->left = left;
            node->right = right;
            treeStack.push(node);
        }
    }

    // If the stack doesn't have exactly one node, it's an invalid expression
    if (treeStack.size() != 1) {
        cerr << "Error: Invalid prefix expression." << endl;
        return nullptr;
    }

    return treeStack.top();  // Root of the tree
}

// Inorder traversal (left, root, right) - generates infix notation
string inorderTraversal(Node* root) {
    if (!root) return "";
    string left = inorderTraversal(root->left);
    string right = inorderTraversal(root->right);
    if (!left.empty() && !right.empty())
        return "(" + left + " " + root->value + " " + right + ")";
    return root->value;
}

// Preorder traversal (root, left, right) - generates prefix notation
string preorderTraversal(Node* root) {
    if (!root) return "";
    return root->value + " " + preorderTraversal(root->left) + preorderTraversal(root->right);
}

// Postorder traversal (left, right, root) - generates postfix notation
string postorderTraversal(Node* root) {
    if (!root) return "";
    return postorderTraversal(root->left) + postorderTraversal(root->right) + root->value + " ";
}

// Evaluates the expression tree recursively
double evaluateExpressionTree(Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right)  // If it's a leaf node (operand)
        return stod(root->value);  // Convert the operand to a double

    double leftVal = evaluateExpressionTree(root->left);
    double rightVal = evaluateExpressionTree(root->right);

    if (root->value == "+")
        return leftVal + rightVal;
    else if (root->value == "-")
        return leftVal - rightVal;
    else if (root->value == "*")
        return leftVal * rightVal;
    else if (root->value == "/")
        return leftVal / rightVal;

    cerr << "Error: Invalid operator in expression tree" << endl;
    return 0;
}

// Detects if the input expression is infix, postfix, or prefix
string detectExpressionType(const string& expression) {
    if (isOperator(string(1, expression[0])))  // If it starts with an operator, it's prefix
        return "prefix";

    if (isOperator(string(1, expression.back())))  // If it ends with an operator, it's postfix
        return "postfix";

    return "infix";  // Otherwise, assume it's infix
}
