#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>

// Класс для времени (ЧЧ:ММ)
class Time {
public:
    int hours;
    int minutes;

    // Конструктор
    Time(int h = 0, int m = 0) : hours(h), minutes(m) {}

    // Преобразование строки в время
    static Time fromString(const std::string& timeStr) {
        int hours = std::stoi(timeStr.substr(0, 2));
        int minutes = std::stoi(timeStr.substr(3, 2));
        return Time(hours, minutes);
    }

    // Преобразование времени в строку
    std::string toString() const {
        char buffer[6];
        snprintf(buffer, sizeof(buffer), "%02d:%02d", hours, minutes);
        return std::string(buffer);
    }

    // Возвращает продолжительность работы в минутах
    int duration(const Time& closeTime) const {
        return (closeTime.hours * 60 + closeTime.minutes) - (hours * 60 + minutes);
    }
};

// Класс для клуба
class Club {
public:
    std::string name;          // Название клуба
    std::string address;       // Адрес клуба
    std::string theme;         // Тематика клуба
    Time open_time;            // Время открытия
    Time close_time;           // Время закрытия

    // Ввод информации о клубе с проверкой на пустые строки
    void input() {
        name = inputString("Название клуба -> ");
        address = inputString("Адрес клуба -> ");
        theme = inputString("Тематика клуба (например, караоке, живая музыка) -> ");
        open_time = inputTime("Время открытия (формат ЧЧ:ММ) -> ");
        close_time = inputTime("Время закрытия (формат ЧЧ:ММ) -> ");
    }

private:
    // Проверка на пустую строку или строку из пробелов
    bool isEmptyOrWhitespace(const std::string& str) {
        return str.empty() || str.find_first_not_of(' ') == std::string::npos;
    }

    // Ввод строки с проверкой на пустые значения
    std::string inputString(const std::string& prompt) {
        std::string result;
        do {
            std::cout << prompt;
            std::getline(std::cin, result);
            if (isEmptyOrWhitespace(result)) {
                std::cout << "Ошибка: значение не может быть пустым!\n";
            }
        } while (isEmptyOrWhitespace(result));
        return result;
    }

    // Ввод времени с проверкой формата
    Time inputTime(const std::string& prompt) {
        std::string timeStr;
        do {
            std::cout << prompt;
            std::getline(std::cin, timeStr);
            if (isEmptyOrWhitespace(timeStr) || timeStr.length() != 5 || timeStr[2] != ':') {
                std::cout << "Ошибка: неправильный формат времени! Попробуйте снова (ЧЧ:ММ).\n";
            } else {
                try {
                    return Time::fromString(timeStr);
                } catch (...) {
                    std::cout << "Ошибка: неправильный формат времени! Попробуйте снова.\n";
                }
            }
        } while (true);
    }
};

// Вывод всех клубов с корректной нумерацией и форматированием
void printClubs(Club* clubs, int n) {
    if (n == 0) {
        std::cout << "\nСписок клубов пуст!\n";
        return;
    }

    std::cout << "\nСписок клубов:\n";
    std::cout << std::setw(5) << "№"
              << std::setw(20) << "Название"
              << std::setw(15) << "Адрес"
              << std::setw(25) << "Тематика"
              << std::setw(25) << "Открытие "
              << std::setw(25) << "Закрытие" << '\n';
    std::cout << "--------------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < n; ++i) {
        std::cout << std::setw(3) << i + 1
                  << std::setw(15) << clubs[i].name
                  << std::setw(20) << clubs[i].address
                  << std::setw(20) << clubs[i].theme
                  << std::setw(15) << clubs[i].open_time.toString()
                  << std::setw(15) << clubs[i].close_time.toString() << '\n';
    }
}

// Поиск клуба с караоке, который работает дольше всех
void findLongestOpenKaraokeClub(Club* clubs, int n) {
    int max_duration = -1;
    Club* longest_open_club = nullptr;

    for (int i = 0; i < n; ++i) {
        if (clubs[i].theme.find("караоке") != std::string::npos || clubs[i].theme.find("Караоке") != std::string::npos) {
            int duration = clubs[i].open_time.duration(clubs[i].close_time);

            if (duration > max_duration) {
                max_duration = duration;
                longest_open_club = &clubs[i];
            }
        }
    }

    if (longest_open_club) {
        std::cout << "\nКлуб с караоке, который работает дольше всех:\n";
        std::cout << "Название: " << longest_open_club->name << '\n';
        std::cout << "Адрес: " << longest_open_club->address << '\n';
        std::cout << "Тематика: " << longest_open_club->theme << '\n';
        std::cout << "Время открытия: " << longest_open_club->open_time.toString() << '\n';
        std::cout << "Время закрытия: " << longest_open_club->close_time.toString() << '\n';
    } else {
        std::cout << "\nНет клубов с караоке.\n";
    }
}

// Вывод меню
void printMenu() {
    std::cout << "\n1. Добавить запись\n";
    std::cout << "2. Показать все записи\n";
    std::cout << "3. Найти клуб с караоке, который работает дольше всех\n";
    std::cout << "0. Выход\n";
    std::cout << "-> ";
}

int main() {
    Club clubs[128];   // Массив для хранения данных о клубах
    int nclubs = 0;    // Количество клубов

    int command;
    do {
        printMenu();
        std::cin >> command;
        std::cin.ignore();  // Очистка буфера после ввода команды

        switch (command) {
            case 1:
                std::cout << "\nДобавление нового клуба:\n";
                clubs[nclubs].input();
                nclubs++;
                break;
            case 2:
                printClubs(clubs, nclubs);
                break;
            case 3:
                findLongestOpenKaraokeClub(clubs, nclubs);
                break;
            case 0:
                std::cout << "\nДо свидания!\n";
                break;
            default:
                std::cout << "\nНеверная команда! Пожалуйста, попробуйте снова.\n";
                break;
        }
    } while (command != 0);

    return 0;
}
