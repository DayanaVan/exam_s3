#include <iostream>

using namespace std;

class Array {
private:
    int* data;
    int capacity;
    int size;

public:
    Array(int firstCap) {  
        if (firstCap <= 0) {
            firstCap = 1;  
        }
        data = new int[firstCap];
        size = 0;
        capacity = firstCap;
    }

    ~Array() {
        delete[] data;
    }

    // resize
    void resize() {
        if (size == capacity) {
            int newCap = 2 * capacity;
            int* newData = new int[newCap];

            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }

            delete[] data;
            data = newData;
            capacity = newCap;
        }
    }

    // add
    void add(int value) {
        resize();
        data[size] = value;
        size++;
    }

    // addAt 
    void addAt(int value, int index) {
        if (index < 0 || index >= size) {
            cout << "invalid index" << endl;
            return;
        }

        resize();
        for (int i = size - 1; i >= index; i--) {
            data[i + 1] = data[i];
        }
        data[index] = value;
        size++;
    }

    // print
    void print() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    // get
    int get(int index) {
        if (index >= 0 && index < size) {
            return data[index];
        }
        return -1;
    }

    // setAt
    void setAt(int index, int value) {
        if (index >= 0 && index < size) {
            data[index] = value;
        }
    }

    // remove
    void remove(int index) {
        if (index < 0 || index >= size) {
            cout << "invalid index" << endl;
            return;
        }

        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }
};

int main() {
    
    Array array(5); 

    array.add(1);
    array.add(2);
    array.add(3);
    array.add(4);
    array.add(5);

    cout << "array: ";
    array.print();

    cout << "adding at index" << endl;
    array.addAt(99, 2);

    cout << "after addAt: ";
    array.print();

    cout << "element with 2 index: " << array.get(2) << endl;

    array.remove(2);
    cout << "after remove: ";
    array.print();

    return 0;
}
