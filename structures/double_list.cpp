#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void Add(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = head;
    newNode->prev = nullptr;
    head = newNode;
}

void Print(Node*& head) {
    Node* printNode = head;
    while (printNode != nullptr) {
        cout << printNode->data << " ";
        printNode = printNode->next;
    }
    cout << endl;
}

int main()
{
    Node* Flist = nullptr; 
    Add(Flist, 4);
    Add(Flist, 5);
    Print(Flist);
}
