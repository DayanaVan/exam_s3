#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <ctime>
#include <stdexcept>
#include <locale.h>


// ==================== СИНГЛТОН СКОТТА МАЙЕРСА ДЛЯ ЛОГГЕРА ====================
class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(const std::string& message, bool isError = false) {
        std::string timestamp = getCurrentTime();
        std::string type = isError ? "[ERROR]" : "[INFO]";
        std::string logMessage = timestamp + " " + type + " " + message;

        std::cout << logMessage << std::endl;

        // Также записываем в файл
        std::ofstream logFile("track_log.txt", std::ios::app);
        if (logFile.is_open()) {
            logFile << logMessage << std::endl;
            logFile.close();
        }
    }

private:
    Logger() {
        // Очищаем файл при запуске
        std::ofstream logFile("track_log.txt", std::ios::trunc);
        logFile.close();
    }

    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::string getCurrentTime() {
        time_t now = time(nullptr);
        char buf[80];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
        return buf;
    }
};

// ==================== КЛАСС ОШИБОК ====================
class MusicError : public std::runtime_error {
public:
    explicit MusicError(const std::string& message)
        : std::runtime_error(message) {
        Logger::getInstance().log("Ошибка: " + message, true);
    }
};

// ==================== БАЗОВЫЙ КЛАСС МУЗЫКАНТА ====================
class Musician {
public:
    virtual ~Musician() = default;

    virtual std::string playDrums() {
        throw MusicError(getName() + " не умеет барабанить!");
    }

    virtual std::string playRhythm() {
        throw MusicError(getName() + " не умеет играть ритм!");
    }

    virtual std::string playSolo() {
        throw MusicError(getName() + " не умеет играть соло!");
    }

    virtual std::string sing() {
        throw MusicError(getName() + " не умеет петь!");
    }

    virtual std::string getName() const = 0;
};

// ==================== КОНКРЕТНЫЕ МУЗЫКАНТЫ ====================
class Drummer : public Musician {
public:
    std::string playDrums() override {
        return "Барабанщик играет на барабанах: Бум-бум-бац!";
    }

    std::string getName() const override { return "Барабанщик"; }
};

class Bassist : public Musician {
public:
    std::string playRhythm() override {
        return "Басист играет ритм: Бум-бум-бум";
    }

    std::string getName() const override { return "Басист"; }
};

class RhythmGuitarist : public Musician {
public:
    std::string playRhythm() override {
        return "Ритм-гитарист играет ритм: Джанг-джанг-джанг";
    }

    std::string playSolo() override {
        return "Ритм-гитарист играет соло: Вжиииууу!";
    }

    std::string getName() const override { return "Ритм-гитарист"; }
};

class SoloGuitarist : public Musician {
public:
    std::string playSolo() override {
        return "Соло-гитарист играет соло: Виззз-вжааах!";
    }

    std::string getName() const override { return "Соло-гитарист"; }
};

class Vocalist : public Musician {
public:
    std::string playRhythm() override {
        return "Вокалист играет ритм на тамбурине: Тинь-тинь-тинь";
    }

    std::string sing() override {
        return "Вокалист поет: Ля-ля-ля, о-о-о!";
    }

    std::string getName() const override { return "Вокалист"; }
};

// ==================== КЛАСС КОМПОНОВЩИКА ====================
class TrackComposer {
private:
    std::vector<std::shared_ptr<Musician>> musicians;
    std::string trackName;

    bool hasDrummer = false;
    bool hasRhythmPlayer = false;
    bool hasBassist = false;

public:
    TrackComposer(const std::string& name) : trackName(name) {
        Logger::getInstance().log("Начало создания трека '" + name + "'");
    }

    void addMusician(std::shared_ptr<Musician> musician) {
        std::string musicianName = musician->getName();
        Logger::getInstance().log("Добавление музыканта: " + musicianName);

        musicians.push_back(musician);

        // Проверяем обязательные требования
        if (dynamic_cast<Drummer*>(musician.get())) hasDrummer = true;
        if (dynamic_cast<Bassist*>(musician.get())) hasBassist = true;

        // Проверяем, может ли музыкант играть ритм
        try {
            musician->playRhythm();
            hasRhythmPlayer = true;
        }
        catch (const MusicError&) {
            // Не может играть ритм - игнорируем
        }
    }

    void compose() {
        Logger::getInstance().log("Компоновка трека '" + trackName + "'...");

        // Проверка обязательных требований
        if (!hasDrummer) {
            throw MusicError("В треке обязательно должен быть барабанщик!");
        }
        if (!hasBassist) {
            throw MusicError("В треке обязательно должен быть басист!");
        }
        if (!hasRhythmPlayer) {
            throw MusicError("В треке обязательно должен быть кто-то, играющий ритм!");
        }

        std::vector<std::string> trackParts;

        // Собираем части трека
        for (auto& musician : musicians) {
            std::string name = musician->getName();

            // Проверяем, чтобы гитарист не барабанил
            if (dynamic_cast<RhythmGuitarist*>(musician.get()) ||
                dynamic_cast<SoloGuitarist*>(musician.get())) {
                try {
                    // Пытаемся заставить гитариста играть на барабанах
                    musician->playDrums();
                    // Если дошли сюда - это ошибка!
                    throw MusicError(name + " пытается играть на барабанах!");
                }
                catch (const MusicError& e) {
                    // Ожидаемо - гитарист не умеет барабанить
                }
            }

            // Добавляем возможные партии
            try {
                trackParts.push_back(musician->playDrums());
            }
            catch (const MusicError&) {}

            try {
                trackParts.push_back(musician->playRhythm());
            }
            catch (const MusicError&) {}

            try {
                trackParts.push_back(musician->playSolo());
            }
            catch (const MusicError&) {}

            try {
                trackParts.push_back(musician->sing());
            }
            catch (const MusicError&) {}
        }

        // Выводим готовый трек
        Logger::getInstance().log("=== ТРЕК '" + trackName + "' ГОТОВ ===");
        for (const auto& part : trackParts) {
            Logger::getInstance().log(part);
        }
        Logger::getInstance().log("=== КОНЕЦ ТРЕКА ===\n");
    }
};

// ==================== СОЗДАНИЕ ТРЕКОВ ====================
int main() {
    setlocale (LC_ALL, "rus");

    try {
        Logger::getInstance().log("========== НАЧАЛО СОЗДАНИЯ АЛЬБОМА ==========");

        // Трек 1: Полный состав
        {
            TrackComposer track1("Рок-н-ролл жив");
            track1.addMusician(std::make_shared<Drummer>());
            track1.addMusician(std::make_shared<Bassist>());
            track1.addMusician(std::make_shared<RhythmGuitarist>());
            track1.addMusician(std::make_shared<SoloGuitarist>());
            track1.addMusician(std::make_shared<Vocalist>());
            track1.compose();
        }

        // Трек 2: Минимальный состав
        {
            TrackComposer track2("Минимализм");
            track2.addMusician(std::make_shared<Drummer>());
            track2.addMusician(std::make_shared<Bassist>());
            track2.addMusician(std::make_shared<RhythmGuitarist>());
            track2.compose();
        }

        // Трек 3: С двумя вокалистами
        {
            TrackComposer track3("Гармония");
            track3.addMusician(std::make_shared<Drummer>());
            track3.addMusician(std::make_shared<Bassist>());
            track3.addMusician(std::make_shared<RhythmGuitarist>());
            track3.addMusician(std::make_shared<Vocalist>());
            track3.addMusician(std::make_shared<Vocalist>());
            track3.compose();
        }

        // Трек 4: Инструментал
        {
            TrackComposer track4("Инструментал");
            track4.addMusician(std::make_shared<Drummer>());
            track4.addMusician(std::make_shared<Bassist>());
            track4.addMusician(std::make_shared<RhythmGuitarist>());
            track4.addMusician(std::make_shared<SoloGuitarist>());
            track4.compose();
        }

        // Трек 5: С ошибкой (нет ритма)
        try {
            TrackComposer track5("Эксперимент");
            track5.addMusician(std::make_shared<Drummer>());
            track5.addMusician(std::make_shared<Bassist>());
            track5.addMusician(std::make_shared<SoloGuitarist>()); // Не играет ритм!
            track5.compose();
        }
        catch (const MusicError& e) {
            Logger::getInstance().log("Не удалось создать трек 'Эксперимент': " + std::string(e.what()));
        }

        Logger::getInstance().log("========== СОЗДАНИЕ АЛЬБОМА ЗАВЕРШЕНО ==========");

    }
    catch (const std::exception& e) {
        Logger::getInstance().log("Критическая ошибка: " + std::string(e.what()), true);
    }

    return 0;
}