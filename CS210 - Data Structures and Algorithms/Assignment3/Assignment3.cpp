// Name: Zana Osman
// Student Number: 200489300
// Date: March 24th, 2024

#include <iostream>
using namespace std;

// TreeNode structure for BST
struct TreeNode {
    int item;
    TreeNode* left;
    TreeNode* right;

    // Constructor for TreeNode
    TreeNode(int value): item(value), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
// Uses recursion to do the function
class BST {
private:
    TreeNode* root;

    // Function to insert a root, if there is no root it will create a new one
    TreeNode* insertItem(TreeNode* root, int item) {
        if (root == nullptr)
            return new TreeNode(item);
        if (item < root->item)
            root->left = insertItem(root->left, item);
        else if (item > root->item)
            root->right = insertItem(root->right, item);

        return root;
    }

    // Function to delete the Node desired from the BST
    TreeNode* deleteNode(TreeNode* root, int item) {
        if (root == nullptr) {
            cout << "Item not found." << endl;
            return root;
        }

        if (item < root->item)
            root->left = deleteNode(root->left, item);
        else if (item > root->item)
            root->right = deleteNode(root->right, item);
        else {
            if (root->left == nullptr) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }

            TreeNode* temp = minvalueNode(root->right);
            root->item = temp->item;
            root->right = deleteNode(root->right, temp->item);
        }
        return root;
    }

    // Find the minimum value within the BST
    TreeNode* minvalueNode(TreeNode* root) {
        TreeNode* temp = root->left;
        while (temp->right != nullptr)
            temp = temp->right;
        return temp;
    }

    // Sort the BST in inorder form
    void inorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return;
        inorderTraversal(root->left);
        cout << root->item << " ";
        inorderTraversal(root->right);
    }

    // Sort the BST in preorder form
    void preorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return;
        cout << root->item << " ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }

    // Sort the BST in postorder form
    void postorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return;
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        cout << root->item << " ";
    }

public:
    // Constructor for the class
    BST() : root(nullptr) {}

    // All functions here call the private functions, the public are easier to call inside int main

    // Function to call that will use the insertItem from the class
    void insert(int item) {
        root = insertItem(root, item);
    }

    // Function to call that will use deleteNode from the class
    void deleteN(int item) {
        root = deleteNode(root, item);
    }

    // Function to call the inorder from the class
    void inorderTraversal() {
        inorderTraversal(root);
        cout << endl;
    }

    // Function to call the preorder from the class
    void preorderTraversal() {
        preorderTraversal(root);
        cout << endl;
    }

    // Function to call the postoder from the class
    void postorderTraversal() {
        postorderTraversal(root);
        cout << endl;
    }
};

int main() {
    BST bst;

    // Define n for integers, num for values to input
    int n;
    cout << "Initially, how many integers you want: ";
    cin >> n;
    cout << "Enter the integers: ";
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        bst.insert(num);
    }

    // Using a do-while so that it can do the switch case and only use the 6 possible operations
    int choice;
    do {
        cout << "Press 1 for inorder traverse, 2 for preorder traverse, 3 for postorder traverse, "
             << "4 for inserting new item, 5 for deleting an item, or 6 for exit the program: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Inorder Traverse: ";
                bst.inorderTraversal();
                break;
            case 2:
                cout << "Preorder Traverse: ";
                bst.preorderTraversal();
                break;
            case 3:
                cout << "Postorder Traverse: ";
                bst.postorderTraversal();
                break;
            case 4:
                int insertItem;
                cout << "Enter the item for insert: ";
                cin >> insertItem;
                bst.insert(insertItem);
                break;
            case 5:
                int deleteItem;
                cout << "Enter the item for delete: ";
                cin >> deleteItem;
                bst.deleteN(deleteItem);
                break;
            case 6:
                cout << "Program terminated" << endl;
                break;
            default:
                cout << "Initemid choice! Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}