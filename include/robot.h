#pragma once
#include <cmath>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "map.h"

// handles everything related to robot phisics
class robotSimulation
{
public:
	robotSimulation(sf::Vector2f start_pos, float start_angle);

	void update();
	void updateMapData();
	void render();

	Map map;

	// public to expose it to the original code
	float servo_angle = 0;

	float imu_angle = 0;

	float motor_speed = 0; // mm / loop
	float total_encoders = 0;

	float left_dist;
	float front_dist;
	float right_dist;

	sf::Vector2i blocks; // (num_red, num_green)

private:
	sf::Vector2f pos;
	float angle = 0;

	float cum_dist = 0;

	const float servo_speed = 0.05f; // rad / loop
	const float cam_fov = M_PI / 2;	  // half the actual fov
	const float encoder_to_mm = 1.6f; // mm / enc
};

extern robotSimulation robot; // WARN TODO: this is global
