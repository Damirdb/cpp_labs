#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
// время отдельной структурой, получить время работы, вместо структур сделать классы, сделать восзможность работать и с char и со string

// Структура для хранения данных о клубах
struct Club {
    std::string name;          // Название клуба
    std::string address;       // Адрес клуба
    std::string theme;         // Тематика клуба (например, караоке, живая музыка)
    std::string open_time;     // Время открытия (формат ЧЧ:ММ)
    std::string close_time;    // Время закрытия (формат ЧЧ:ММ)
};

// Функция для проверки пустой строки (или строки с пробелами)
bool isEmptyOrWhitespace(const std::string &str) {
    return str.empty() || str.find_first_not_of(' ') == std::string::npos;
}

// Ввод информации о клубе с проверкой на пустые строки
void inputClub(Club* club) {
    do {
        std::cout << "Название клуба -> ";
        std::getline(std::cin, club->name);
        if (isEmptyOrWhitespace(club->name)) {
            std::cout << "Ошибка: название не может быть пустым!\n";
        }
    } while (isEmptyOrWhitespace(club->name));

    do {
        std::cout << "Адрес клуба -> ";
        std::getline(std::cin, club->address);
        if (isEmptyOrWhitespace(club->address)) {
            std::cout << "Ошибка: адрес не может быть пустым!\n";
        }
    } while (isEmptyOrWhitespace(club->address));

    do {
        std::cout << "Тематика клуба (например, караоке, живая музыка) -> ";
        std::getline(std::cin, club->theme);
        if (isEmptyOrWhitespace(club->theme)) {
            std::cout << "Ошибка: тематика не может быть пустой!\n";
        }
    } while (isEmptyOrWhitespace(club->theme));

    do {
        std::cout << "Время открытия (формат ЧЧ:ММ) -> ";
        std::getline(std::cin, club->open_time);
        if (isEmptyOrWhitespace(club->open_time)) {
            std::cout << "Ошибка: время открытия не может быть пустым!\n";
        }
    } while (isEmptyOrWhitespace(club->open_time));

    do {
        std::cout << "Время закрытия (формат ЧЧ:ММ) -> ";
        std::getline(std::cin, club->close_time);
        if (isEmptyOrWhitespace(club->close_time)) {
            std::cout << "Ошибка: время закрытия не может быть пустым!\n";
        }
    } while (isEmptyOrWhitespace(club->close_time));
}

// Вывод всех клубов с корректной нумерацией и форматированием
void printClubs(Club* clubs, int n) {
    if (n == 0) {
        std::cout << "\nСписок клубов пуст!\n";
        return;
    }

    std::cout << "\nСписок клубов:\n";
    std::cout << std::setw(5) << "№" << std::setw(20) << "Название" << std::setw(30) << "Адрес" << std::setw(25) << "Тематика" << std::setw(15) << "Открытие" << std::setw(15) << "Закрытие" << '\n';
    std::cout << "------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < n; ++i) {
        std::cout << std::setw(5) << i + 1
                  << std::setw(20) << clubs[i].name
                  << std::setw(30) << clubs[i].address
                  << std::setw(25) << clubs[i].theme
                  << std::setw(15) << clubs[i].open_time
                  << std::setw(15) << clubs[i].close_time << '\n';
    }
}

// Преобразование времени (ЧЧ:ММ) в минуты для сравнения
int timeToMinutes(const std::string& time) {
    int hours = std::stoi(time.substr(0, 2));
    int minutes = std::stoi(time.substr(3, 2));
    return hours * 60 + minutes;
}

// Поиск клуба с караоке, который работает дольше всех
void findLongestOpenKaraokeClub(Club* clubs, int n) {
    int max_duration = -1;
    Club* longest_open_club = nullptr;

    for (int i = 0; i < n; ++i) {
        if (clubs[i].theme.find("караоке") != std::string::npos || clubs[i].theme.find("Караоке") != std::string::npos) {
            int open_time = timeToMinutes(clubs[i].open_time);
            int close_time = timeToMinutes(clubs[i].close_time);
            int duration = close_time - open_time;

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
        std::cout << "Время открытия: " << longest_open_club->open_time << '\n';
        std::cout << "Время закрытия: " << longest_open_club->close_time << '\n';
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
                inputClub(&clubs[nclubs]);
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

    return 0; // возможно нао удалить
}
