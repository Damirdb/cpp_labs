#include "VIPKaraokeClub.h"
#include <iostream>

VIPKaraokeClub::VIPKaraokeClub() : KaraokeClub(), hasPrivateRooms(false) {}

VIPKaraokeClub::VIPKaraokeClub(const std::string& n, const std::string& a, const Time& open, const Time& close, int r, bool priv)
    : KaraokeClub(n, a, open, close, r), hasPrivateRooms(priv) {}

void VIPKaraokeClub::input() {
    KaraokeClub::input();
    std::cout << "Есть ли приватные комнаты (1 - да, 0 - нет) -> ";
    std::cin >> hasPrivateRooms;
}

void VIPKaraokeClub::print() const {
    KaraokeClub::print();
    std::cout << "Приватные комнаты: " << (hasPrivateRooms ? "Да" : "Нет") << '\n';
}
