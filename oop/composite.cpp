#include <iostream>
using namespace std;

class Item { // общий интерфейс
public:
    virtual void print() = 0;
    virtual ~Item() {}
};

class SimpleItem : public Item { // лист
private:
    int value;

public:
    SimpleItem(int v) : value(v) {}

    void print() override {
        cout << value << endl;
    }
};

class ItemGroup : public Item { // компоновщик
private:
    Item* a;
    Item* b;

public:
    ItemGroup(Item* x, Item* y) : a(x), b(y) {}

    void print() override {
        a->print();
        b->print();
    }
};

int main() {
    Item* i1 = new SimpleItem(1);
    Item* i2 = new SimpleItem(2);

    Item* group = new ItemGroup(i1, i2);

    group->print();
}
