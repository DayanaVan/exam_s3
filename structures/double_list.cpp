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

void deleteBeg(Node*& head) {
    if (head == nullptr) {
        return;
    }

    Node* deleteNode = head;
    head = head->next;
    delete deleteNode;
}

void AddEnd(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = newNode;
    newNode->prev = current;
}

void DeleteEnd(Node*& head) {
    if (head == nullptr) {
        return;
    }

    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    
    current->prev->next = nullptr;  
    delete current;
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
    AddEnd(Flist, 9);
    Print(Flist);

    deleteBeg(Flist);
    Print(Flist);

    DeleteEnd(Flist);
    Print(Flist);
}
