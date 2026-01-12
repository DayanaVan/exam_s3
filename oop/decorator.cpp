#include <iostream>
using namespace std;

class Coffee { // интерфейс компонента
public:
    virtual int cost() = 0;
    ~Coffee() {}
};

class simpleCoffee : public Coffee { // конкретный компонент
public:
    int cost() override {
        return 50;
    }
};

class coffeeDecorator : public Coffee { // базовый декоратор
protected:
    Coffee* coffee;
public:
    coffeeDecorator(Coffee* c) : coffee(c) {}
};

class MilkDecorator : public coffeeDecorator { // конкретный декоратор
public:
    MilkDecorator(Coffee* c) : coffeeDecorator(c) {}

    int cost() override {
        return coffee->cost() + 20;
    }
};

int main() {
    Coffee* coffee = new simpleCoffee(); 
    coffee = new MilkDecorator(coffee);

    cout << "Стоимость кофе: " << coffee->cost() << endl;

    delete coffee;
}
