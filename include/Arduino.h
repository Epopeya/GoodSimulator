#pragma once
#include <chrono>
#include <cmath>

const auto program_start_time = std::chrono::high_resolution_clock::now();
const float PI = M_PI;

const int INPUT_PULLUP = 2;
const int OUTPUT = 1;
const int LOW = 0;
const int HIGH = 1;

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
}

void pinMode(int pin, int mode) {}
void digitalWrite(int pin, int status)
{
}
int digitalRead(int pin)
{
	return 0;
}

float constrain(float value, float min_value, float max_value)
{
	return fmin(max_value, fmax(value, min_value));
}

typedef struct
{
	float x;
	float y;
} vector2_t;

typedef struct
{
	int x;
	int y;
} vector2_integer_t;
