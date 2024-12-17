#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <vector>

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

    Time operator+(int minutes) const {
        int totalMinutes = h * 60 + m + minutes;
        totalMinutes %= 1440; // Учитываем переход через полночь
        return Time(totalMinutes / 60, totalMinutes % 60);
    }

    Time operator-(int minutes) const {
        int totalMinutes = h * 60 + m - minutes;
        while (totalMinutes < 0) totalMinutes += 1440; // Учитываем переход через полночь
        return Time(totalMinutes / 60, totalMinutes % 60);
    }

    Time& operator++() { // Префиксный инкремент
        *this = *this + 1;
        return *this;
    }

    Time operator++(int) { // Постфиксный инкремент
        Time temp = *this;
        ++(*this);
        return temp;
    }

    Time& operator--() { // Префиксный декремент
        *this = *this - 1;
        return *this;
    }

    Time operator--(int) { // Постфиксный декремент
        Time temp = *this;
        --(*this);
        return temp;
    }

    bool operator<(const Time& other) const { // Сравнение < 
        return (h * 60 + m) < (other.h * 60 + other.m);
    }

    std::string toString() const {
        char buffer[6];
        snprintf(buffer, sizeof(buffer), "%02d:%02d", h, m);
        return std::string(buffer);
    }
};

// Класс для клуба (базовый класс)
class Club {
protected:
    std::string name, address, theme; // Название, адрес, тематика
    Time openTime, closeTime;         // Время открытия, закрытия

public:
    Club() {}

    Club(const std::string& name, const std::string& address, const std::string& theme, const Time& open, const Time& close)
        : name(name), address(address), theme(theme), openTime(open), closeTime(close) {}

    virtual void display() const {
        std::cout << "Название: " << name << "\n"
                  << "Адрес: " << address << "\n"
                  << "Тематика: " << theme << "\n"
                  << "Время открытия: " << openTime.toString() << "\n"
                  << "Время закрытия: " << closeTime.toString() << "\n";
    }

    virtual ~Club() = default; // Виртуальный деструктор
};

// Класс для клуба с караоке (наследник от Club)
class KaraokeClub : public Club {
public:
    KaraokeClub(const std::string& name, const std::string& address, const Time& open, const Time& close)
        : Club(name, address, "Караоке", open, close) {}

    void display() const override {
        Club::display();
        std::cout << "Тип клуба: Караоке\n";
    }
};

// Класс для клуба с живой музыкой (наследник от Club)
class LiveMusicClub : public Club {
public:
    LiveMusicClub(const std::string& name, const std::string& address, const Time& open, const Time& close)
        : Club(name, address, "Живая музыка", open, close) {}

    void display() const override {
        Club::display();
        std::cout << "Тип клуба: Живая музыка\n";
    }
};

// Дружественная функция для доступа к времени открытия и закрытия клуба
class FriendClass {
public:
    void printClubTimes(const Club& club) {
        std::cout << "Открытие: " << club.openTime.toString() << ", Закрытие: " << club.closeTime.toString() << "\n";
    }
};

// Функция для вывода всех клубов
void printAllClubs(const std::vector<Club*>& clubs) {
    for (const auto& club : clubs) {
        club->display();
        std::cout << "----------------------------\n";
    }
}

int main() {
    std::vector<Club*> clubs;

    Time openTime1(18, 0), closeTime1(23, 0);
    KaraokeClub karaokeClub("Karaoke Paradise", "Улица Ленина, 15", openTime1, closeTime1);

    Time openTime2(19, 30), closeTime2(2, 0);
    LiveMusicClub liveMusicClub("Live Music Stage", "Улица Пушкина, 5", openTime2, closeTime2);

    clubs.push_back(&karaokeClub);
    clubs.push_back(&liveMusicClub);

    FriendClass friendObj;
    friendObj.printClubTimes(karaokeClub);

    printAllClubs(clubs);

    return 0;
}

