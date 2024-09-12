#pragma once
#include "Arduino.h"
#include "robot.h"
#include <vector>

// External variable declarations
extern float front_distance;
extern float right_distance;
extern float left_distance;

// Function declarations
void lidarSetup();
std::vector<float> lidarInitialDistances();
void lidarStart();
