#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

void add(Node*& top, int value) {
    Node* addNode = new Node;
    addNode->data = value;
    addNode->next = nullptr;

    if (top == nullptr) {
        top = addNode;
        return;
    }

    Node* current = top;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = addNode;
}

void delete1(Node*& top) {
    if (top == nullptr) {
        return;
    }

    Node* deleteNode = top;
    Node* prev = nullptr;
    while (deleteNode->next != nullptr) {
        prev = deleteNode;
        deleteNode = deleteNode->next;
    }
    prev->next = nullptr;
    delete deleteNode;
}

void addBeginning(Node*& top, int value) {
    Node* addBegin = new Node;
    addBegin->data = value;
    addBegin->next = top;
    top = addBegin;
}

int getCount(Node*& top) {
    int q = 0;
    Node* current = top;
    while (current != nullptr) {
        q++;
        current = current->next;
    }
    return q;
}

void addAt(Node*& top, int value, int position) {
    int length = getCount(top);

    if (position < 0 || position > length) {
        cout << "Wrong position" << endl;
        return;
    }

    if (position == 0) {
        addBeginning(top, value);
    }
    else if (position == length) {
        add(top, value);
    }
    else {
        Node* current = top;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = current->next;
        current->next = newNode;
    }

}

void print(Node*& top) {
    Node* printNode = top;
    while (printNode != nullptr) {
        cout << printNode->data << " ";
        printNode = printNode->next;
    }
    cout << endl;
}

int main()
{
    Node* test = nullptr;
    add(test, 1);
    add(test, 2);
    add(test, 3);
    print(test);

    addBeginning(test, 4);
    print(test);

    addAt(test, 5, 1);
    print(test);

    delete1(test);
    print(test);
}

