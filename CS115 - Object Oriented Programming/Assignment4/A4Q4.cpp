#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* FindK(Node* head, int k) {
    Node* middle = head;
    Node* top = head;
    
    while (top != NULL && top->next != NULL) {
        middle = middle->next;
        top = top->next->next;
    }
    
    for (int i = 0; i < k && middle != NULL; ++i) {
        middle = middle->next;
    }
    
    return middle;
}

int main() {
    cout << "Enter the values for the linked list (enter -1 to stop): ";
    cout << endl;

    int value;

    Node* head = NULL;
    Node* tail = NULL;
    
    while (true) {
        cin >> value;

        if (value == -1)
            break;

        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = head;

        head = newNode;
    }

    int k;
    cout << "Enter the value of k: ";
    cin >> k;
    
    Node* kNode = FindK(head, k);
    
    if (kNode != NULL) {
        cout << "The kth N from the middle is: " << kNode->data << endl;
    } else {
        cout << "Invalid value of k." << endl;
    }
    
    Node* current = head;
    Node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }

    return 0;
}
