#pragma once
#include "debug.h"
#include <Arduino.h>

class PID {
public:
    PID(float KP, float KI, float KD);
    float update(float value);
    float target;

private:
    unsigned long last_update;
    float last_value;
    float KP;
    float KI;
    float KD;
    float cumulative_error;
    float last_error;
};
