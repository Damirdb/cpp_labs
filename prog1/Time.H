#ifndef TIME_H
#define TIME_H

#include <string>

class Time {
    int h, m;

public:
    Time();
    Time(int hours, int minutes);
    void input();
    std::string toString() const;
    int duration(const Time& close) const;

    friend class TimeHelper;
};

class TimeHelper {
public:
    static void printTimeDifference(const Time& t1, const Time& t2);
};

#endif // TIME_H
