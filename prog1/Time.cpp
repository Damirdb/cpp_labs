#include "Time.h"
#include <iostream>
#include <stdexcept>
#include <cstdio>

Time::Time() : h(0), m(0) {}

Time::Time(int hours, int minutes) {
    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
        throw std::invalid_argument("Недопустимое время.");
    }
    h = hours;
    m = minutes;
}

void Time::input() {
    while (true) {
        std::cout << "Введите часы (0-23): ";
        std::cin >> h;
        std::cout << "Введите минуты (0-59): ";
        std::cin >> m;
        if (h >= 0 && h < 24 && m >= 0 && m < 60) {
            break;
        } else {
            std::cout << "Ошибка: некорректное время. Попробуйте снова.\n";
        }
    }
}

std::string Time::toString() const {
    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", h, m);
    return std::string(buffer);
}

int Time::duration(const Time& close) const {
    int start = h * 60 + m;
    int end = close.h * 60 + close.m;
    if (end < start) end += 24 * 60;
    return end - start;
}

void TimeHelper::printTimeDifference(const Time& t1, const Time& t2) {
    int diff = t1.duration(t2);
    std::cout << "Разница во времени: " << diff / 60 << " ч " << diff % 60 << " мин\n";
}
