#pragma once
#include <cstdio>
#include <stddef.h>

#include "Arduino.h"

void debug_init() {};
void debug_msg(const char* format, ...)
{
	printf(format);
	printf("\n");
};
void debug_target_direction(float angle) {};
void debug_current_direction(float angle) {};
void debug_battery(float voltage) {};
void debug_position(vector2_t pos) {};
void debug_waypoints(vector2_t waypoints[], size_t waypoints_len) {};
void debug_lidar(vector2_t pos) {};
void debug_map_flip(bool flipped) {};
