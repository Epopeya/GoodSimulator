#include "pid.h"

// Constructor definition
PID::PID(float KP, float KI, float KD)
    : KP(KP)
    , KI(KI)
    , KD(KD)
    , last_update(micros())
    , cumulative_error(0)
    , last_error(0)
{
}

// Function definition
float PID::update(float value)
{
    unsigned long current_time = micros();
    float dt = (current_time - last_update) * 1e-6;

    float error = target - value;
    cumulative_error += error * dt;
    float error_rate = (error - last_error) / dt;
    float output = KP * error + KI * cumulative_error + KD * error_rate;

    // Debugging message (commented out for now)
    // debug_msg("error: %f, XP: %f, XI: %f, XD: %f, out: %f\n", error, error * KP, KI * cumulative_error,
    //           KD * error_rate, output);

    last_update = current_time;
    last_error = error;

    return output;
}
