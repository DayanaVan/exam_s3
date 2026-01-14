#include <iostream>
using namespace std;

class Transport {
private:
    int year;
    string brand;

public:
    Transport(int inputYear, string inputBrand) : year(inputYear), brand(inputBrand) {}

    ~Transport() {}

    virtual void Driving() {
        cout << "Transport is basically driving" << endl;
    }
};

class Car : public Transport {
private:
    int horsePower;
    string carType;

public:
    Car() : Transport(2025, "Daewoo"), horsePower(150), carType("Matiz") {}

    Car(int year, string brand, int inputHorsePower, string inputCarType) :  Transport(year, brand), horsePower(inputHorsePower), carType(inputCarType) {}

    ~Car() {}

    void Driving() override {
        cout << "Car is driving very fast" << endl;
    }
};

class Race {
private:
    Car* cars;
    int capacity;
    int size;

private:
    void resize() {
        if (size >= capacity) {
            int newCapacity = 2 * capacity;
            Car* newCars = new Car[newCapacity];

            for (int i = 0; i < size; i++) {
                newCars[i] = cars[i];
            }

            delete[] cars;
            cars = newCars;
            capacity = newCapacity;
        }
    }

public:
    ~Race() 
    {
        delete[] cars;
    }

    Race(int inputCapacity) : capacity(inputCapacity), size(0) 
    {
        cars = new Car[capacity];
    }

    void put(Car& car) {
        resize();
        cars[size] = car;
        size++;
        cout << "Car successfully added to the end!" << endl;
    }

    void put(Car& car, int index) {
        
        if (index < 0 || index > size) {
            cout << "Invalid index" << endl;
            return;
        }

        resize();

        for (int i = size; i > index; i--) {
            cars[i] = cars[i - 1];
        }

        cars[index] = car;
        size++;
        cout << "Car successfully added at index " << index << endl;
    }

    Car* get(int index) {
        if (index >= 0 && index < size) {
            return &cars[index];
        }
        return nullptr;
    }

    int getSize() {
        return size;
    }

    operator int() const {
        return size;
    }
};

int main()
{
    // класс транспорт
    Transport transport(2020, "unknown");
    transport.Driving();

    // класс автомобиль
    Car car1(2000, "Mazda", 100, "Sedan");
    Car car2(1800, "Kareta", 3, "Troyka");
    Car car3(2025, "Ferrari", 400, "Sportcar");
    cout << endl;

    car1.Driving();
    car2.Driving();
    car3.Driving();
    cout << endl;

    // класс гонка
    Race race(5);

    // put
    race.put(car1);
    race.put(car2);
    race.put(car3, 0);

    // get ?
    if (race.get(0) != nullptr) {
        cout << "Car with index 0 IS exicting" << endl;
    }
    else {
        cout << "Car with index 0 IS NOT exicting" << endl;
    }

    // size (getSize)
    cout << "Current size of the race: " << race.getSize() << endl;

    // приведение типа
    int count = static_cast<int>(race);
    cout << "\nRace as int: " << count << endl;

    return 0;
}
