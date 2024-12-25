#include "DanceClub.h"
#include <iostream>

DanceClub::DanceClub() : Club(), maxCapacity(0) {}

DanceClub::DanceClub(const std::string& n, const std::string& a, const Time& open, const Time& close, int cap)
    : Club(n, a, "Танцы", open, close), maxCapacity(cap) {}

void DanceClub::input() {
    theme = "Танцы";
    Club::input();
    std::cout << "Максимальная вместимость -> ";
    std::cin >> maxCapacity;
}

void DanceClub::print() const {
    Club::print();
    std::cout << "Максимальная вместимость: " << maxCapacity << '\n';
}
