#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* next;
};

void Push(Node*& top, int value) {
	Node* newNode = new Node;
	newNode->data = value;
	newNode->next = top;
	top = newNode;
}

void Pop(Node*& top) {
	if (top == nullptr) return;

	Node* deleteNode = top; 
	top = top->next;
	delete deleteNode;
}

void Print(Node*& top) {
	Node* printNode = top;
	while (printNode != nullptr) {
		cout << printNode->data << " ";
		printNode = printNode->next;
	}
	cout << endl;
}

int main() {
	Node* stack = nullptr;
	Push(stack, 3);
	Print(stack);
	Pop(stack);
	Print(stack);
}
