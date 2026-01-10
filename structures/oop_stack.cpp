#include <iostream>

using namespace std;

class Stack {
private:
    struct Node {
        int data;
        Node* next;
    };

    Node* top;

public:
    Stack() {
        top = nullptr;
    }

    ~Stack() {
        while (top != nullptr) {
            Pop();
        }
    }

    void Push(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    void Pop() {
        if (top == nullptr) return;

        Node* deleteNode = top;
        top = top->next;
        delete deleteNode;
    }

    void Print() {
        Node* printNode = top;
        while (printNode != nullptr) {
            cout << printNode->data << " ";
            printNode = printNode->next;
        }
        cout << endl;
    }
};

int main() {
    Stack stack; 

    stack.Push(3);
    stack.Print();
    stack.Pop();
    stack.Print();

    return 0;
}
