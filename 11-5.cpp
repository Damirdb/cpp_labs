#include <iostream>
#include <string>
#include <iomanip>
// #include <windows.h>
#include <locale>

/* Установка кодировки консоли для корректного отображения кириллицы
void setupConsole() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru_RU.UTF-8");
}
 */

// Класс для времени (ЧЧ:ММ)
class Time {
    int h, m;

public:
    // Конструкторы
    Time() : h(0), m(0) {}
    Time(int hours, int minutes) : h(hours), m(minutes) {}
    Time(const Time& other) : h(other.h), m(other.m) {}
    Time(const std::string& timeStr) : h(std::stoi(timeStr.substr(0, 2))), m(std::stoi(timeStr.substr(3, 2))) {}

    // Методы
    std::string toString() const {
        char buffer[6];
        snprintf(buffer, sizeof(buffer), "%02d:%02d", h, m);
        return std::string(buffer);
    }

    int duration(const Time& close) const {
        int start = h * 60 + m;
        int end = close.h * 60 + close.m;
        if (end < start) end += 24 * 60;  // Учет перехода через полночь
        return end - start;
    }
};

// Класс для клуба
class Club {
    std::string n, a, t; // Название, адрес, тематика
    Time ot, ct;         // Время открытия, закрытия

public:
    // Конструкторы
    Club() {}
    Club(const std::string& name, const std::string& address, const std::string& theme, const Time& open, const Time& close)
        : n(name), a(address), t(theme), ot(open), ct(close) {}
    Club(const Club& other) : n(other.n), a(other.a), t(other.t), ot(other.ot), ct(other.ct) {}

    // Методы
    void input() {
        std::cout << "Название клуба -> ";
        std::cin.ignore();
        std::getline(std::cin, n);

        std::cout << "Адрес клуба -> ";
        std::getline(std::cin, a);

        std::cout << "Тематика клуба (например, караоке, живая музыка) -> ";
        std::getline(std::cin, t);

        std::string openTimeStr, closeTimeStr;
        std::cout << "Время открытия (формат ЧЧ:ММ) -> ";
        std::getline(std::cin, openTimeStr);
        ot = Time(openTimeStr);

        std::cout << "Время закрытия (формат ЧЧ:ММ) -> ";
        std::getline(std::cin, closeTimeStr);
        ct = Time(closeTimeStr);
    }

    std::string getName() const { return n; }
    std::string getAddress() const { return a; }
    std::string getTheme() const { return t; }
    Time getOpenTime() const { return ot; }
    Time getCloseTime() const { return ct; }
};

// Функция для вывода списка клубов
void printClubs(Club* clubs, int n) {
    if (n == 0) {
        std::cout << "\nСписок клубов пуст!\n";
        return;
    }

    std::cout << "\nСписок клубов:\n";
    std::cout << std::setw(5) << "№"
              << std::setw(25) << "Название"
              << std::setw(20) << "Адрес"
              << std::setw(25) << "Тематика"
              << std::setw(20) << "Открытие"
              << std::setw(20) << "Закрытие" << '\n';
    std::cout << std::string(100, '-') << std::endl;

    for (int i = 0; i < n; ++i) {
        std::cout << std::setw(3) << i + 1
                  << std::setw(20) << clubs[i].getName()
                  << std::setw(22) << clubs[i].getAddress()
                  << std::setw(20) << clubs[i].getTheme()
                  << std::setw(12) << clubs[i].getOpenTime().toString()
                  << std::setw(10) << clubs[i].getCloseTime().toString() << '\n';
    }
}

// Функция для поиска клуба с караоке, который работает дольше всех
void findLongestKaraokeClub(Club* clubs, int n) {
    int maxDuration = -1, index = -1;

    for (int i = 0; i < n; ++i) {
        if (clubs[i].getTheme() == "караоке" || clubs[i].getTheme() == "Караоке") {
            int duration = clubs[i].getOpenTime().duration(clubs[i].getCloseTime());
            if (duration > maxDuration) {
                maxDuration = duration;
                index = i;
            }
        }
    }

    if (index != -1) {
        std::cout << "\nКлуб с караоке, который работает дольше всех:\n";
        std::cout << std::setw(15) << "Название"
                  << std::setw(25) << "Адрес"
                  << std::setw(30) << "Часы работы\n";
        std::cout << std::string(65, '-') << std::endl;
        std::cout << std::setw(15) << clubs[index].getName()
                  << std::setw(25) << clubs[index].getAddress()
                  << std::setw(15) << maxDuration / 60 << " ч " << maxDuration % 60 << " мин\n";
    } else {
        std::cout << "\nКлубы с караоке не найдены.\n";
    }
}

// Функция для вывода меню
void printMenu() {
    std::cout << "\n1. Добавить запись\n";
    std::cout << "2. Показать все записи\n";
    std::cout << "3. Найти клуб с караоке, который работает дольше всех\n";
    std::cout << "0. Выход\n";
    std::cout << "-> ";
}

int main() {
   // setupConsole();  // Установка кодировки для Windows

    Club clubs[128];
    int nclubs = 0;

    int command;
    do {
        printMenu();
        std::cin >> command;

        switch (command) {
            case 1:
                if (nclubs < 128) {
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
                findLongestKaraokeClub(clubs, nclubs);
                break;
            case 0:
                std::cout << "\nДо свидания!\n";
                break;
            default:
                std::cout << "\nНеверная команда! Попробуйте снова.\n";
                break;
        }
    } while (command != 0);

    return 0;
}
