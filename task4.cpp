#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>

using namespace std;

// Базовый класс материала
class Material {
public:
    virtual string getType() const = 0;
    virtual ~Material() = default;
};

// Конкретные материалы
class Brick : public Material {
public:
    string getType() const override { return "кирпич"; }
};

class Concrete : public Material {
public:
    string getType() const override { return "бетон"; }
};

class Wood : public Material {
public:
    string getType() const override { return "дерево"; }
};

// Базовый класс специалиста
class Specialist {
public:
    virtual string getSpecialization() const = 0;
    virtual bool canWorkWith(const string& material) const = 0;
    virtual ~Specialist() = default;
};

// Конкретные специалисты
class Bricklayer : public Specialist {
public:
    string getSpecialization() const override { return "каменщик"; }
    bool canWorkWith(const string& material) const override {
        return material == "кирпич" || material == "бетон";
    }
};

class Electrician : public Specialist {
public:
    string getSpecialization() const override { return "электрик"; }
    bool canWorkWith(const string& material) const override {
        return material == "дерево"; // Электрик работает только с деревом (проводка)
    }
};

class Carpenter : public Specialist {
public:
    string getSpecialization() const override { return "плотник"; }
    bool canWorkWith(const string& material) const override {
        return material == "дерево";
    }
};

// Класс для обработки исключений
class ConstructionException : public exception {
private:
    string message;
public:
    ConstructionException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Класс здания
class Building {
private:
    string name;
    string material;
    vector<string> specialists;

public:
    Building(const string& n, const string& m) : name(n), material(m) {}

    void addSpecialist(const string& specialist) {
        specialists.push_back(specialist);
    }

    string getName() const { return name; }
    string getMaterial() const { return material; }

    void display() const {
        cout << "Здание: " << name << " (материал: " << material << ")\n";
        cout << "Специалисты: ";
        for (const auto& s : specialists) {
            cout << s << " ";
        }
        cout << "\n";
    }
};

// Фабрика зданий
class BuildingFactory {
public:
    static unique_ptr<Building> createBuilding(const string& name,
        const string& material,
        const vector<string>& specialists) {
        // Проверка совместимости специалистов с материалом
        for (const auto& specName : specialists) {
            unique_ptr<Specialist> specialist = createSpecialist(specName);
            if (!specialist->canWorkWith(material)) {
                throw ConstructionException("Ошибка: специалист '" + specName +
                    "' не может работать с материалом '" + material + "'");
            }
        }

        auto building = make_unique<Building>(name, material);
        for (const auto& spec : specialists) {
            building->addSpecialist(spec);
        }

        return building;
    }

private:
    static unique_ptr<Specialist> createSpecialist(const string& type) {
        if (type == "каменщик") return make_unique<Bricklayer>();
        if (type == "электрик") return make_unique<Electrician>();
        if (type == "плотник") return make_unique<Carpenter>();
        throw ConstructionException("Неизвестный тип специалиста: " + type);
    }
};

// Класс запроса на строительство
class ConstructionRequest {
private:
    string buildingName;
    string material;
    vector<string> requiredSpecialists;

public:
    ConstructionRequest(const string& name, const string& mat,
        const vector<string>& specs)
        : buildingName(name), material(mat), requiredSpecialists(specs) {}

    bool verifyBuilding(const Building& building) const {
        if (building.getName() != buildingName || building.getMaterial() != material) {
            return false;
        }

        // Здесь можно добавить более сложную проверку
        return true;
    }

    string getName() const { return buildingName; }
    string getMaterial() const { return material; }

    void display() const {
        cout << "Запрос: " << buildingName << " (материал: " << material << ")\n";
        cout << "Требуемые специалисты: ";
        for (const auto& s : requiredSpecialists) {
            cout << s << " ";
        }
        cout << "\n";
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    vector<ConstructionRequest> requests;
    vector<unique_ptr<Building>> buildings;

    // Создаем 5 запросов на строительство
    requests.push_back(ConstructionRequest("Дом", "кирпич", { "каменщик", "электрик" }));
    requests.push_back(ConstructionRequest("Гараж", "бетон", { "каменщик" }));
    requests.push_back(ConstructionRequest("Баня", "дерево", { "плотник", "электрик" }));
    requests.push_back(ConstructionRequest("Склад", "бетон", { "каменщик", "электрик" }));
    requests.push_back(ConstructionRequest("Беседка", "дерево", { "плотник" }));

    cout << "=== ЗАПРОСЫ НА СТРОИТЕЛЬСТВО ===\n";
    for (const auto& req : requests) {
        req.display();
        cout << "------------------------\n";
    }

    cout << "\n=== СТРОИТЕЛЬСТВО ЗДАНИЙ ===\n";

    // Пытаемся построить здания по запросам
    for (size_t i = 0; i < requests.size(); ++i) {
        cout << "\nСтроительство " << i + 1 << ": " << requests[i].getName() << "\n";

        try {
            // Специально создадим ошибку для демонстрации
            vector<string> specialists;

            if (i == 2) { // Для бани создадим ошибку - неправильный специалист
                specialists = { "плотник", "каменщик" }; // Каменщик не может работать с деревом
            }
            else {
                // Используем специалистов из запроса
                if (requests[i].getMaterial() == "кирпич") {
                    specialists = { "каменщик" };
                    if (i == 0) specialists.push_back("электрик");
                }
                else if (requests[i].getMaterial() == "бетон") {
                    specialists = { "каменщик" };
                }
                else if (requests[i].getMaterial() == "дерево") {
                    specialists = { "плотник" };
                    if (i == 2) specialists.push_back("электрик");
                }
            }

            auto building = BuildingFactory::createBuilding(
                requests[i].getName(),
                requests[i].getMaterial(),
                specialists
            );

            // Проверяем соответствие запросу
            if (requests[i].verifyBuilding(*building)) {
                cout << "Здание построено и соответствует запросу\n";
                building->display();
                buildings.push_back(move(building));
            }
            else {
                throw ConstructionException("Здание не соответствует запросу");
            }

        }
        catch (const ConstructionException& e) {
            cout << e.what() << "\n";
        }
    }

    cout << "\n=== ИТОГ ===\n";
    cout << "Успешно построено зданий: " << buildings.size() << " из 5\n";

    return 0;
}