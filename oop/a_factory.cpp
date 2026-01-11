#include <iostream>
using namespace std;

class Button { // абстрактный продукт 1
public:
    virtual void Click() = 0;
    ~Button() {}
};

class Monitor { // абстрактный продукт 2
public:
    virtual void Display() = 0;
    ~Monitor() {}
};

class windowsButton : public Button { // конкретный продукт 1.1
public:
    void Click() override {
        cout << "Windows button" << endl;
    }
};

class windowsMonitor : public Monitor { // конкретный продукт 2.1
public:
    void Display() override {
        cout << "Windows monitor" << endl;
    }
};

class abstFactory { // абстрактная фабрика
public:
    virtual Button* createButton() = 0;
    virtual Monitor* createMonitor() = 0;
    ~abstFactory() {}
};

class windowsFactory : public abstFactory { // конкретная фабрика
public:
    Button* createButton() override {
        return new windowsButton();
    }

    Monitor* createMonitor() override {
        return new windowsMonitor;
    }
};

int main() {
    abstFactory* factory;

    factory = new windowsFactory();

    Button* button = factory->createButton();
    Monitor* monitor = factory->createMonitor();

    button->Click();
    monitor->Display();

    delete button;
    delete monitor;
    delete factory;
}
