#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>

// Класс для времени (ЧЧ:ММ)
class Time {
    int h, m;

public:
    Time() : h(0), m(0) {}

    Time(int hours, int minutes) {
        if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
            throw std::invalid_argument("Недопустимое время.");
        }
        h = hours;
        m = minutes;
    }

    void input() {
        while (true) {
            std::cout << "Введите часы (0-23): ";
            std::cin >> h;
            std::cout << "Введите минуты (0-59): ";
            std::cin >> m;
            if (h >= 0 && h < 24 && m >= 0 && m < 60) {
                break;
            } else {
                std::cout << "Ошибка: некорректное время. Попробуйте снова.\n";
            }
        }
    }

    std::string toString() const {
        char buffer[6];
        snprintf(buffer, sizeof(buffer), "%02d:%02d", h, m);
        return std::string(buffer);
    }

    int duration(const Time& close) const {
        int start = h * 60 + m;
        int end = close.h * 60 + close.m;
        if (end < start) end += 24 * 60; // Учет перехода через полночь
        return end - start;
    }

    friend class TimeHelper; // Дружественный класс
};

// Дружественный класс для операций с временем
class TimeHelper {
public:
    static void printTimeDifference(const Time& t1, const Time& t2) {
        int diff = t1.duration(t2);
        std::cout << "Разница во времени: " << diff / 60 << " ч " << diff % 60 << " мин\n";
    }
};

// Базовый класс Клуб
class Club {
protected:
    std::string name;
    std::string address;
    std::string theme;
    Time openTime;
    Time closeTime;

public:
    Club() {}

    Club(const std::string& n, const std::string& a, const std::string& t, const Time& open, const Time& close)
        : name(n), address(a), theme(t), openTime(open), closeTime(close) {}

    virtual void input() {
        std::cout << "Название клуба -> ";
        std::cin.ignore();
        std::getline(std::cin, name);

        std::cout << "Адрес клуба -> ";
        std::getline(std::cin, address);

        std::cout << "Тематика клуба (например, караоке, живая музыка) -> ";
        std::getline(std::cin, theme);

        std::cout << "Время открытия:\n";
        openTime.input();

        std::cout << "Время закрытия:\n";
        closeTime.input();
    }

    virtual void print() const {
        std::cout << std::setw(5) << "№"
              << std::setw(25) << "Название"
              << std::setw(20) << "Адрес"
              << std::setw(25) << "Тематика"
              << std::setw(20) << "Открытие"
              << std::setw(20) << "Закрытие" << '\n';
        std::cout << std::string(100, '-') << std::endl;
        std::cout << std::setw(15) << name
                  << std::setw(20) << address
                  << std::setw(15) << theme
                  << std::setw(10) << openTime.toString()
                  << std::setw(10) << closeTime.toString() << '\n';
    }

    std::string getTheme() const { return theme; }
    Time getOpenTime() const { return openTime; }
    Time getCloseTime() const { return closeTime; }

    virtual ~Club() {}
};

// Наследник Клуба: Караоке
class KaraokeClub : public Club {
    int rooms;

public:
    KaraokeClub() : Club(), rooms(0) {}

    KaraokeClub(const std::string& n, const std::string& a, const Time& open, const Time& close, int r)
        : Club(n, a, "Караоке", open, close), rooms(r) {}

    void input() override {
        Club::input();
        std::cout << "Количество комнат -> ";
        std::cin >> rooms;
    }

    void print() const override {
        Club::print();
        std::cout << "Количество комнат: " << rooms << '\n';
    }
};

// Наследник Клуба: Танцевальный клуб
class DanceClub : public Club {
    int maxCapacity;

public:
    DanceClub() : Club(), maxCapacity(0) {}

    DanceClub(const std::string& n, const std::string& a, const Time& open, const Time& close, int cap)
        : Club(n, a, "Танцы", open, close), maxCapacity(cap) {}

    void input() override {
        Club::input();
        std::cout << "Максимальная вместимость -> ";
        std::cin >> maxCapacity;
    }

    void print() const override {
        Club::print();
        std::cout << "Максимальная вместимость: " << maxCapacity << '\n';
    }
};

// Наследник КараокеКлуба: VIP Караоке
class VIPKaraokeClub : public KaraokeClub {
    bool hasPrivateRooms;

public:
    VIPKaraokeClub() : KaraokeClub(), hasPrivateRooms(false) {}

    VIPKaraokeClub(const std::string& n, const std::string& a, const Time& open, const Time& close, int r, bool priv)
        : KaraokeClub(n, a, open, close, r), hasPrivateRooms(priv) {}

    void input() override {
        KaraokeClub::input();
        std::cout << "Есть ли приватные комнаты (1 - да, 0 - нет) -> ";
        std::cin >> hasPrivateRooms;
    }

    void print() const override {
        KaraokeClub::print();
        std::cout << "Приватные комнаты: " << (hasPrivateRooms ? "Да" : "Нет") << '\n';
    }
};

// Главная программа
int main() {
    Club* clubs[128];
    int nclubs = 0;

    int command;
    do {
        std::cout << "\n1. Добавить общий клуб\n2. Добавить караоке клуб\n3. Добавить танцевальный клуб\n4. Добавить VIP караоке\n5. Показать клубы\n0. Выход\n-> ";
        std::cin >> command;

        switch (command) {
            case 1:
                clubs[nclubs] = new Club();
                clubs[nclubs]->input();
                nclubs++;
                break;
            case 2:
                clubs[nclubs] = new KaraokeClub();
                clubs[nclubs]->input();
                nclubs++;
                break;
            case 3:
                clubs[nclubs] = new DanceClub();
                clubs[nclubs]->input();
                nclubs++;
                break;
            case 4:
                clubs[nclubs] = new VIPKaraokeClub();
                clubs[nclubs]->input();
                nclubs++;
                break;
            case 5:
                for (int i = 0; i < nclubs; ++i) {
                    clubs[i]->print();
                }
                break;
            case 0:
                for (int i = 0; i < nclubs; ++i) {
                    delete clubs[i];
                }
                std::cout << "\nДо свидания!\n";
                break;
            default:
                std::cout << "\nНеверная команда! Попробуйте снова.\n";
                break;
        }
    } while (command != 0);

    return 0;
}
