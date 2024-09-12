#include "timer.h"

// Constructor definition
Timer::Timer(int time)
    : time(time)
    , last_time(millis())
{
}

// Function definition
bool Timer::primed()
{
    unsigned long current_time = millis();
    if ((current_time - last_time) > time) {
        last_time = current_time;
        return true;
    } else {
        return false;
    }
}
