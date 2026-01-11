#include <iostream>

using namespace std;

class Transport { // интерфейс продукта
public:
    virtual void deliver() = 0;
    virtual ~Transport() {}
};

class Truck : public Transport { // конкретный продукт 1
public:
    void deliver() override {
        cout << "Delivery by truck" << endl;
    }
};

class Ship : public Transport { // конкретный продукт 2
public:
    void deliver() override {
        cout << "Delivery by ship" << endl;
    }
};

class Logistics { // создатель (фабрика)
public:
    virtual Transport* createTransport() = 0;

    void planDelivery() {
        Transport* transport = createTransport();
        transport->deliver();
        delete transport;
    }

    virtual ~Logistics() {}
};

class roadLogistics : public Logistics { // конкретный создатель 1 (конкретная фабрика 1)
public:
    Transport* createTransport() override {
        return new Truck();
    }
};

class seaLogistics : public Logistics { // конкретный создатель 2  (конкретная фабрика 2)
public:
    Transport* createTransport() override {
        return new Ship();
    }
};

int main() {
    Logistics* logistics;

    cout << "Earth delivery:" << endl;
    logistics = new roadLogistics();
    logistics->planDelivery();
    delete logistics;

    cout << "\nSea delivery:" << endl;
    logistics = new seaLogistics();
    logistics->planDelivery();
    delete logistics;
}
