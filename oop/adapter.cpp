#include <iostream>
using namespace std;

class Printer { // какой-то новый интерфейс
public:
    virtual void print() = 0;
    ~Printer() {}
};

class oldPrinter { // старый класс
public:
    void oldPrint() {
        cout << "old printer" << endl;
    }
};

class printerAdapter : public Printer { // адаптер
private:
    oldPrinter* oldprinter;
public:
    printerAdapter(oldPrinter* printer) : oldprinter(printer) {}

    void print() override {
        oldprinter->oldPrint();
    }

};

int main() {
    oldPrinter oldPrinter;

    // используем адаптер
    Printer* printer = new printerAdapter(&oldPrinter);

    printer->print();

    delete printer;
    return 0;
}
