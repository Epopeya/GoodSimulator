#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "map.h"

// handles everything related to robot phisics
class robotSimulation
{
public:
	robotSimulation(sf::Vector2f start_pos, float start_angle);

	void updateMovement(); // dt in seconds
	void updateDistances();
	void render(sf::RenderWindow* window);

	// public to expose it to the original code
	sf::Vector2f pos;
	float angle = 0;
	float servo_angle = 0;
	float servo_speed = 0.045f; // rad / sec < 0.05

	float motor_speed = 0; // mm / sec
	float total_encoders = 0;

	float left_dist;
	float front_dist;
	float right_dist;

private:
	const float encoder_to_mm = 1.6f;
	float cum_dist = 0; // used to calculate encoders
};

extern robotSimulation robot; // WARN TODO: this is global
