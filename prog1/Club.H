#ifndef CLUB_H
#define CLUB_H

#include "Time.h"
#include <string>

class Club {
protected:
    std::string name;
    std::string address;
    std::string theme;
    Time openTime;
    Time closeTime;

public:
    Club();
    Club(const std::string& n, const std::string& a, const std::string& t, const Time& open, const Time& close);
    virtual void input();
    virtual void print() const;
    virtual ~Club();
};

#endif // CLUB_H
