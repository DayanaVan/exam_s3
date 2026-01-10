#include <iostream>

using namespace std;

class Queue {
private:
    struct Node {
        int data;
        Node* next;
    };
    Node* front;
public:
    Queue() {
        front = nullptr;
    }
    ~Queue() {
        while (front != nullptr) {
            Pop();
        }
    }

    void Push(int value) {
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

    void Pop() {
        Node* deleteNode = front;
        front = front->next;
        delete deleteNode;
    }

    void Print() {
        Node* current = front;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

};

int main()
{
    Queue queue;
    queue.Push(5);
    queue.Print();
    queue.Pop();
    queue.Print();
}
