#include <iostream>
using namespace std;

class House { // продукт
public:
    bool walls = false;
    bool roof = false;
    bool garage = false;

    void show() {
        cout << "Дом:\n";
        cout << "Стены: " << (walls ? "есть" : "нет") << endl;
        cout << "Крыша: " << (roof ? "есть" : "нет") << endl;
        cout << "Гараж: " << (garage ? "есть" : "нет") << endl;
    }
};

class HouseBuilder { // интерфейс строителя
protected:
    House* house;
public:
    HouseBuilder() {
        house = new House();
    }

    virtual void buildWalls() = 0;
    virtual void buildRoof() = 0;
    virtual void buildGarage() = 0;

    House* getHouse() {
        return house;
    }
};

class SimpleHouseBuilder : public HouseBuilder { // строитель
public:
    void buildWalls() override {
        house->walls = true;
    }

    void buildRoof() override {
        house->roof = true;
    }

    void buildGarage() override {
        house->garage = false;
    }
};

int main() {
    HouseBuilder* builder = new SimpleHouseBuilder();

    builder->buildWalls();
    builder->buildRoof();
    builder->buildGarage();

    House* house = builder->getHouse();
    house->show();

    delete house;
    delete builder;
    return 0;
}

