#include "map.h"

#include <cmath>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

void renderMap(sf::RenderWindow* window)
{
	sf::RectangleShape center_block(sf::Vector2f(1000, 1000));
	sf::RectangleShape outer_walls(sf::Vector2f(3000, 3000));

	center_block.setPosition(1000, -2000);
	center_block.setFillColor(sf::Color(255, 0, 0));

	outer_walls.setPosition(0, -3000);
	outer_walls.setFillColor(sf::Color(0, 0, 0, 0));
	outer_walls.setOutlineColor(sf::Color(0, 255, 0));
	outer_walls.setOutlineThickness(100);

	window->draw(center_block);
	window->draw(outer_walls);
}

float getRayIntersect(sf::Vector2f ray_pos, float ray_angle)
{
	sf::RectangleShape center_block(sf::Vector2f(1000, 1000));
	sf::RectangleShape outer_walls(sf::Vector2f(3000, 3000));
	center_block.setPosition(1000, 1000);
	outer_walls.setPosition(0, 0);

	float dist = 10000;

	sf::Vector2f p1 = sf::Vector2f(0, 0);
	sf::Vector2f p2 = sf::Vector2f(3000, 0);
	sf::Vector2f p3 = sf::Vector2f(3000, 3000);
	sf::Vector2f p4 = sf::Vector2f(0, 3000);

	dist = fmin(rayLineDist(ray_pos, ray_angle, p1, p2), dist);
	dist = fmin(rayLineDist(ray_pos, ray_angle, p2, p3), dist);
	dist = fmin(rayLineDist(ray_pos, ray_angle, p3, p4), dist);
	dist = fmin(rayLineDist(ray_pos, ray_angle, p4, p1), dist);

	sf::Vector2f q1 = sf::Vector2f(1000, 1000);
	sf::Vector2f q2 = sf::Vector2f(2000, 1000);
	sf::Vector2f q3 = sf::Vector2f(2000, 2000);
	sf::Vector2f q4 = sf::Vector2f(1000, 2000);

	dist = fmin(rayLineDist(ray_pos, ray_angle, q1, q2), dist);
	dist = fmin(rayLineDist(ray_pos, ray_angle, q2, q3), dist);
	dist = fmin(rayLineDist(ray_pos, ray_angle, q3, q4), dist);
	dist = fmin(rayLineDist(ray_pos, ray_angle, q4, q1), dist);

	return dist;
}

float rayLineDist(sf::Vector2f ray_pos, float angle, sf::Vector2f p2, sf::Vector2f p3)
{
	sf::Vector2f p0 = ray_pos;
	sf::Vector2f p1 = ray_pos + sf::Vector2f(cos(angle), sin(angle)) * 500000.0f;
	sf::Vector2f s1 = p1 - p0;
	sf::Vector2f s2 = p3 - p2;

	float s, t;
	s = (-s1.y * (p0.x - p2.x) + s1.x * (p0.y - p2.y)) / (-s2.x * s1.y + s1.x * s2.y);
	t = (s2.x * (p0.y - p2.y) - s2.y * (p0.x - p2.x)) / (-s2.x * s1.y + s1.x * s2.y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		sf::Vector2f inter = p0 + (t * s1);
		sf::Vector2f dist = inter - ray_pos;
		// Collision detected
		return std::sqrt(dist.x * dist.x + dist.y * dist.y);
	}

	return 50000; // No collision
}
