#ifndef KARAOKECLUB_H
#define KARAOKECLUB_H

#include "Club.h"

class KaraokeClub : public Club {
    int rooms;

public:
    KaraokeClub();
    KaraokeClub(const std::string& n, const std::string& a, const Time& open, const Time& close, int r);
    void input() override;
    void print() const override;
};

#endif // KARAOKECLUB_H
