#ifndef DANCECLUB_H
#define DANCECLUB_H

#include "Club.h"

class DanceClub : public Club {
    int maxCapacity;

public:
    DanceClub();
    DanceClub(const std::string& n, const std::string& a, const Time& open, const Time& close, int cap);
    void input() override;
    void print() const override;
};

#endif // DANCECLUB_H
