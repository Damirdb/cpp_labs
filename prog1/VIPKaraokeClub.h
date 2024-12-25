#ifndef VIPKARAOKECLUB_H
#define VIPKARAOKECLUB_H

#include "KaraokeClub.h"

class VIPKaraokeClub : public KaraokeClub {
    bool hasPrivateRooms;

public:
    VIPKaraokeClub();
    VIPKaraokeClub(const std::string& n, const std::string& a, const Time& open, const Time& close, int r, bool priv);
    void input() override;
    void print() const override;
};

#endif // VIPKARAOKECLUB_H
