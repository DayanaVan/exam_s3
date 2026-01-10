#include <iostream>

using namespace std;

struct Array {
	int* data;
	int capacity;
	int size;
};

void create(Array& arr, int firstCap) {
	arr.data = new int[firstCap];
	arr.size = 0;
	arr.capacity = firstCap;
}

void resize(Array& arr) {
	if (arr.size == arr.capacity) {
		int newCap = 2 * arr.capacity;
		int* newData = new int[newCap];

		for (int i = 0; i < arr.size; i++) {
			newData[i] = arr.data[i];
		}

		delete[] arr.data;
		arr.data = newData;
		arr.capacity = newCap;
	}
}

void add(Array& arr, int value) {
	resize(arr);
	arr.data[arr.size] = value;
	arr.size++;
}

void addAt(Array& arr, int value, int index) {
	if (index < 0 || index >= arr.size) {
		cout << "invalid index" << endl;
		return;
	}

	resize(arr);
	for (int i = arr.size - 1; i >= index; i--) { // вот это в шпору
		arr.data[i + 1] = arr.data[i];
	}
	arr.data[index] = value;
	arr.size++;
}

void print(Array& arr) {
	for (int i = 0; i < arr.size; i++) {
		cout << arr.data[i] << " ";
	}
	cout << endl;
}

int get(Array& arr, int index) {
	if (index >= 0 && index < arr.size) {
		return arr.data[index];
	}
	return -1;
}

void setAt(Array& arr, int index, int value) {
	if (index >= 0 && index < arr.size) {
		arr.data[index] = value;
	}
}

void remove(Array& arr, int index) {
	if (index < 0 || index >= arr.size) {
		cout << "invalid index" << endl;
		return;
	}

	for (int i = index; i < arr.size - 1; i++) { // и вот это
		arr.data[i] = arr.data[i + 1];
	}
	arr.size--;
}

int main() {
	Array array;
	create(array, 3);
	add(array, 1);
	add(array, 2);
	add(array, 3);
	print(array);
	cout << "adding at index" << endl;
	addAt(array, 99, 2);
	print(array);
	cout << get(array, 2) << endl;
	remove(array, 2);
	print(array);
}
