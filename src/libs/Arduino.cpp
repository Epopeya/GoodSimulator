#include "Arduino.h"

// Function definitions
unsigned long micros()
{
    auto time_diff = std::chrono::high_resolution_clock::now() - program_start_time;
    unsigned long duration = std::chrono::duration_cast<std::chrono::microseconds>(time_diff).count();
    return duration;
}

unsigned long millis()
{
    auto time_diff = std::chrono::high_resolution_clock::now() - program_start_time;
    unsigned long duration = std::chrono::duration_cast<std::chrono::milliseconds>(time_diff).count();
    return duration;
}

void delay(int time)
{
    // Intentionally left empty
}

void pinMode(int pin, int mode)
{
    // Intentionally left empty
}

void digitalWrite(int pin, int status)
{
    // Intentionally left empty
}

int digitalRead(int pin)
{
    return 0;
}

float constrain(float value, float min_value, float max_value)
{
    return fmin(max_value, fmax(value, min_value));
}
