#include "robot.h"

#include <cmath>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "map.h"
#include "math.h"

robotSimulation::robotSimulation(sf::Vector2f start_pos, float start_angle)
	: pos(start_pos)
	, angle(start_angle)
{
}

void robotSimulation::updateMovement()
{
	updateDistances();
	servo_angle = fmin(fmax(servo_angle, -M_PI / 4), M_PI / 4);
	angle += (servo_angle * servo_speed); // servo is reversed
	sf::Vector2f direction_vector = sf::Vector2f(cos(angle), sin(angle));
	direction_vector = direction_vector * motor_speed;

	cum_dist += motor_speed / encoder_to_mm;
	int encoder_diff = floor(cum_dist);
	/* printf("cum: %f, enc: %i\n", cum_dist, encoder_diff); */
	cum_dist -= encoder_diff;
	total_encoders += encoder_diff;
	/* printf("angle: %f, servo: %f, speed: %f, encoders: %i\n", angle, servo_angle, motor_speed, encoder_diff); */
	/* printf("x: %f, y: %f\n", pos.x - 1500, pos.y); */

	pos += direction_vector;
}

void robotSimulation::updateDistances()
{
	left_dist = getRayIntersect(pos, angle + (M_PI / 2));
	front_dist = getRayIntersect(pos, angle);
	right_dist = getRayIntersect(pos, angle - (M_PI / 2));
}

void robotSimulation::render(sf::RenderWindow* window)
{
	sf::Vector2f flip_pos = sf::Vector2f(pos.x, -pos.y);

	sf::RectangleShape rayShape(sf::Vector2f(10000, 10));
	rayShape.setFillColor(sf::Color(150, 150, 150));
	rayShape.setOrigin(0, 5);
	rayShape.setPosition(flip_pos);

	float left_angle = -(angle + M_PI / 2);
	float front_angle = -(angle);
	float right_angle = -(angle - M_PI / 2);

	// left
	rayShape.setRotation(left_angle * (360 / (2 * M_PI)));
	rayShape.setSize(sf::Vector2f(left_dist, 3));
	window->draw(rayShape);

	// front
	rayShape.setRotation(front_angle * (360 / (2 * M_PI)));
	rayShape.setSize(sf::Vector2f(front_dist, 3));
	window->draw(rayShape);

	// right
	rayShape.setRotation(right_angle * (360 / (2 * M_PI)));
	rayShape.setSize(sf::Vector2f(right_dist, 3));
	window->draw(rayShape);

	sf::CircleShape rayMarker(25);
	rayMarker.setOrigin(25, 25);

	// left
	rayMarker.setPosition(flip_pos + sf::Vector2f(cos(left_angle), sin(left_angle)) * left_dist);
	window->draw(rayMarker);

	// front
	rayMarker.setPosition(flip_pos + sf::Vector2f(cos(front_angle), sin(front_angle)) * front_dist);
	window->draw(rayMarker);

	// right
	rayMarker.setPosition(flip_pos + sf::Vector2f(cos(right_angle), sin(right_angle)) * right_dist);
	window->draw(rayMarker);

	sf::RectangleShape bodyShape(sf::Vector2f(200, 300));
	bodyShape.setFillColor(sf::Color(255, 255, 255));
	bodyShape.setOrigin(100, 150);
	bodyShape.setPosition(flip_pos);
	bodyShape.setRotation(-angle * (360 / (2 * M_PI)) - 90);
	window->draw(bodyShape);

	sf::CircleShape bodyCenter(25);
	bodyCenter.setFillColor(sf::Color(255, 0, 0));
	bodyCenter.setOrigin(25, 25);
	bodyCenter.setPosition(flip_pos);
	window->draw(bodyCenter);
}

// main robot
robotSimulation robot = robotSimulation(sf::Vector2f(1500, 500), 0);
