#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

void Push(Node*& front, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (front == nullptr) {
        front = newNode;
        return;
    }

    Node* current = front;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = newNode;
}

void Pop(Node*& front) {
    Node* deleteNode = front;
    front = front->next;
    delete deleteNode;
}

void Print(Node*& front) {
    Node* current = front;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}


int main()
{
    Node* queue = nullptr;
    Push(queue, 5);
    Print(queue);
    Pop(queue);
    Print(queue);
}
