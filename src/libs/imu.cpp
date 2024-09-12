#include "imu.h"

// Constructor definition
Imu::Imu() { }

// Function definitions
void Imu::setup() { }

int Imu::update()
{
    rotation = robot.imu_angle;
    return true;
}
