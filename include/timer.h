#pragma once
#include <Arduino.h>

class Timer {
public:
    Timer(int time);
    bool primed();

private:
    int time;
    unsigned long last_time;
};
