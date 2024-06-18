#pragma once
#include "Arduino.h"
#include "robot.h"

extern float front_distance = 0;
extern float right_distance = 0;
extern float left_distance = 0;
void lidarSetup() {};
vector2_t lidarInitialPosition()
{
	vector2_t out;
	out.x = 1500;
	out.y = 500;
	return out;
};
void lidarStart() {};
