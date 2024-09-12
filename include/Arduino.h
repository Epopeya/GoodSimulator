#pragma once
#include "debug.h"
#include "vector.h"
#include <chrono>
#include <cmath>

// Constants
const auto program_start_time = std::chrono::high_resolution_clock::now();
const float PI = M_PI;

const int INPUT_PULLUP = 2;
const int OUTPUT = 1;
const int LOW = 0;
const int HIGH = 1;

// Function declarations
unsigned long micros();
unsigned long millis();
void delay(int time);
void pinMode(int pin, int mode);
void digitalWrite(int pin, int status);
int digitalRead(int pin);
float constrain(float value, float min_value, float max_value);
