#pragma once
#include "robot.h"

class Imu
{
public:
	Imu() {};
	void setup() {};
	int update()
	{
		rotation = robot.imu_angle;
		return true;
	};
	float rotation = 0;
};
