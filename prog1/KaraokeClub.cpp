#include "KaraokeClub.h"
#include <iostream>

KaraokeClub::KaraokeClub() : Club(), rooms(0) {}

KaraokeClub::KaraokeClub(const std::string& n, const std::string& a, const Time& open, const Time& close, int r)
    : Club(n, a, "Караоке", open, close), rooms(r) {}

void KaraokeClub::input() {
    theme = "Караоке";
    Club::input();
    std::cout << "Количество комнат -> ";
    std::cin >> rooms;
}

void KaraokeClub::print() const {
    Club::print();
    std::cout << "Количество комнат: " << rooms << '\n';
}
