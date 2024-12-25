#include "Club.h"
#include <iostream>
#include <iomanip>

Club::Club() {}

Club::Club(const std::string& n, const std::string& a, const std::string& t, const Time& open, const Time& close)
    : name(n), address(a), theme(t), openTime(open), closeTime(close) {}

void Club::input() {
    std::cout << "Название клуба -> ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Адрес клуба -> ";
    std::getline(std::cin, address);

    if (theme.empty()) {
        std::cout << "Тематика клуба (например, караоке, живая музыка) -> ";
        std::getline(std::cin, theme);
    }

    std::cout << "Время открытия:\n";
    openTime.input();

    std::cout << "Время закрытия:\n";
    closeTime.input();
}

void Club::print() const {
    std::cout << std::setw(25) << "Название"
              << std::setw(20) << "Адрес"
              << std::setw(25) << "Тематика"
              << std::setw(20) << "Открытие"
              << std::setw(20) << "Закрытие" << '\n';
    std::cout << std::string(100, '-') << std::endl;
    std::cout << std::setw(25) << name
              << std::setw(20) << address
              << std::setw(25) << theme
              << std::setw(20) << openTime.toString()
              << std::setw(20) << closeTime.toString() << '\n';
}

Club::~Club() {}
