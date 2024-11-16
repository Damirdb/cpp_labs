#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <locale>

// Установка кодировки консоли для корректного отображения кириллицы
void setupConsole() {
    SetConsoleCP(1251);           // Кодировка для ввода с консоли
    SetConsoleOutputCP(1251);     // Кодировка для вывода в консоль
    setlocale(LC_ALL, "ru_RU.UTF-8"); // Локаль для русского языка
}

// Класс для времени (ЧЧ:ММ)
class Time {
public:
    int hours;
    int minutes;

    // Конструкторы
    Time(int h = 0, int m = 0) : hours(h), minutes(m) {}

    Time(const std::string& timeStr) {  // Конструктор, принимающий строку
        hours = std::stoi(timeStr.substr(0, 2));
        minutes = std::stoi(timeStr.substr(3, 2));
    }

    // Преобразование в строку
    std::string toString() const {
        char buffer[6];
        snprintf(buffer, sizeof(buffer), "%02d:%02d", hours, minutes);
        return std::string(buffer);
    }

    // Метод для расчета продолжительности работы клуба
    int duration(const Time& closeTime) const {
        int start_minutes = hours * 60 + minutes;
        int end_minutes = closeTime.hours * 60 + closeTime.minutes;

        if (end_minutes < start_minutes) {
            end_minutes += 24 * 60;  // Учет перехода через полночь
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

    // Конструкторы
    Club() {}

    Club(const std::string& name, const std::string& address, const std::string& theme, const Time& open_time, const Time& close_time) 
        : name(name), address(address), theme(theme), open_time(open_time), close_time(close_time) {}

    // Ввод данных о клубе с использованием std::cin
    void input() {
        std::cout << "Название клуба -> ";
        std::cin.ignore();  // Игнорируем символ новой строки после выбора меню
        std::getline(std::cin, name);

        std::cout << "Адрес клуба -> ";
        std::getline(std::cin, address);

        std::cout << "Тематика клуба (например, караоке, живая музыка) -> ";
        std::getline(std::cin, theme);

        std::string openTimeStr, closeTimeStr;
        std::cout << "Время открытия (формат ЧЧ:ММ) -> ";
        std::getline(std::cin, openTimeStr);
        open_time = Time(openTimeStr);

        std::cout << "Время закрытия (формат ЧЧ:ММ) -> ";
        std::getline(std::cin, closeTimeStr);
        close_time = Time(closeTimeStr);
    }
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
              << std::setw(25) << "Адрес"
              << std::setw(30) << "Тематика"
              << std::setw(20) << "Открытие"
              << std::setw(20) << "Закрытие" << '\n';
    std::cout << std::string(100, '-') << std::endl;

    for (int i = 0; i < n; ++i) {
        std::cout << std::setw(3) << i + 1
                  << std::setw(20) << clubs[i].name
                  << std::setw(20) << clubs[i].address
                  << std::setw(20) << clubs[i].theme
                  << std::setw(10) << clubs[i].open_time.toString()
                  << std::setw(10) << clubs[i].close_time.toString() << '\n';
    }
}

// Функция для поиска клуба с караоке, который работает дольше всех
void findLongestKaraokeClub(Club* clubs, int n) {
    int maxDuration = -1;
    int index = -1;

    for (int i = 0; i < n; ++i) {
        if (clubs[i].theme == "караоке" || clubs[i].theme == "Караоке") {
            int duration = clubs[i].open_time.duration(clubs[i].close_time);
            if (duration > maxDuration) {
                maxDuration = duration;
                index = i;
            }
        }
    }

    if (index != -1) {
        std::cout << "\nКлуб с караоке, который работает дольше всех:\n";
        std::cout << std::setw(25) << "Название"
                  << std::setw(30) << "Адрес"
                  << std::setw(10) << "Часы работы\n";
        std::cout << std::string(65, '-') << std::endl;
        std::cout << std::setw(25) << clubs[index].name
                  << std::setw(30) << clubs[index].address
                  << maxDuration / 60 << " ч " << maxDuration % 60 << " мин\n";
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
    setupConsole();  // Установка кодировки для Windows

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
