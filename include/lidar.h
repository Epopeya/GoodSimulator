#pragma once
#include "Arduino.h"
#include "robot.h"

extern float front_distance = robot.front_dist;
extern float right_distance = robot.right_dist;
extern float left_distance = robot.left_dist;
void lidarSetup() {
};
vector2_t lidarInitialPosition()
{
	vector2_t out;
	out.x = robot.front_dist;
	out.y = robot.left_dist;
	return out;
};
void lidarStart() {};
