#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h> // Для SetConsoleCP и SetConsoleOutputCP
#include <locale>
#include <cstring>

// Установка кодировки консоли для корректного отображения кириллицы
void setupConsole() {
    SetConsoleCP(1251);           // Кодировка для ввода с консоли
    SetConsoleOutputCP(1251);     // Кодировка для вывода в консоль
    setlocale(LC_ALL, "ru_RU.UTF-8"); // Установка локали для русского языка
}

// Класс для времени (ЧЧ:ММ)
class Time {
public:
    int hours;
    int minutes;

    Time(int h = 0, int m = 0) : hours(h), minutes(m) {}

    static Time fromString(const std::string& timeStr) {
        int h = std::stoi(timeStr.substr(0, 2));
        int m = std::stoi(timeStr.substr(3, 2));
        return Time(h, m);
    }

    std::string toString() const {
        char buffer[6];
        snprintf(buffer, sizeof(buffer), "%02d:%02d", hours, minutes);
        return std::string(buffer);
    }

    int duration(const Time& closeTime) const {
        int start_minutes = hours * 60 + minutes;
        int end_minutes = closeTime.hours * 60 + closeTime.minutes;

        if (end_minutes < start_minutes) {
            end_minutes += 24 * 60;
        }

        return end_minutes - start_minutes;
    }
};

class Club {
public:
    std::string name;
    std::string address;
    std::string theme;
    Time open_time;
    Time close_time;

    void input() {
        name = inputString("Название клуба -> ");
        address = inputString("Адрес клуба -> ");
        theme = inputString("Тематика клуба (например, караоке, живая музыка) -> ");
        open_time = inputTime("Время открытия (формат ЧЧ:ММ) -> ");
        close_time = inputTime("Время закрытия (формат ЧЧ:ММ) -> ");
    }

private:
    bool isEmptyOrWhitespace(const std::string& str) {
        return str.empty() || str.find_first_not_of(' ') == std::string::npos;
    }

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

void printClubs(Club* clubs, int n) {
    if (n == 0) {
        std::cout << "\nСписок клубов пуст!\n";
        return;
    }

    std::cout << "\nСписок клубов:\n";
    std::cout << std::setw(5) << "№"
              << std::setw(25) << "Название"
              << std::setw(30) << "Адрес"
              << std::setw(25) << "Тематика"
              << std::setw(15) << "Открытие"
              << std::setw(15) << "Закрытие" << '\n';
    std::cout << "-------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < n; ++i) {
        std::cout << std::setw(3) << i + 1
                  << std::setw(25) << clubs[i].name
                  << std::setw(30) << clubs[i].address
                  << std::setw(25) << clubs[i].theme
                  << std::setw(15) << clubs[i].open_time.toString()
 << std::setw(15) << clubs[i].close_time.toString() << '\n';
    }
}

void printMenu() {
    std::cout << "\n1. Добавить запись\n";
    std::cout << "2. Показать все записи\n";
    std::cout << "3. Найти клуб с караоке, который работает дольше всех\n";
    std::cout << "0. Выход\n";
    std::cout << "-> ";
}

int main() {
    setupConsole(); // Установка кодировки для Windows

    Club clubs[128];
    int nclubs = 0;

    int command;
    do {
        printMenu();
        std::cin >> command;
        std::cin.ignore();

        switch (command) {
            case 1:
                if (nclubs < 128) { // Предотвращаем переполнение массива
                    std::cout << "\nДобавление нового клуба:\n";
                    clubs[nclubs].input();
                    nclubs++;
                } else {
                    std::cout << "Ошибка: Превышено максимальное количество клубов.\n";
                }
                break;
            case 2:
                printClubs(clubs, nclubs);
                break;
            case 3:
                // здесь будет функция поиска клуба с караоке, который работает дольше всех
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
