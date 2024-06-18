#pragma once
#include <Arduino.h>

#include "debug.h"

class PID
{
public:
	PID(float KP, float KI, float KD)
		: KP(KP)
		, KI(KI)
		, KD(KD)
		, last_update(micros())
	{
	}
	float update(float value)
	{
		unsigned long current_time = micros();
		float dt = (current_time - last_update) * 1e-6;

		float error = target - value;
		cumulative_error += error * dt;
		float error_rate = (error - last_error) / dt;
		float output = KP * error + KI * cumulative_error + KD * error_rate;

		/* debug_msg("error: %f, XP: %f, XI: %f, XD: %f, out: %f\n", error, error * KP, KI * cumulative_error, */
		/* 	KD * error_rate, output); */

		last_update = current_time;
		last_error = error;

		return output;
	};
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
