#pragma once
#include <cmath>
#include <vector>

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

class Map
{
public:
	Map();

	float getRayIntersect(sf::Vector2f ray_pos, float ray_angle);
	float getRayIntersect(sf::Vector2f ray_pos, sf::Vector2f ray_end);
	sf::Vector2i getVisibleBlocks(sf::Vector2f pos, float angle); // (num_red, num_green)
	void render(sf::RenderWindow* window);

	sf::RectangleShape inner_rect;
	sf::RectangleShape outer_rect;

	std::vector<sf::Vector2f> red_blocks = {sf::Vector2f(2500, 1500), sf::Vector2f(1500, 500)};
	std::vector<sf::Vector2f> green_blocks = {sf::Vector2f(1500, 2500), sf::Vector2f(500, 1500)};
	/* std::vector<sf::Vector2f> red_blocks = {}; */
	/* std::vector<sf::Vector2f> green_blocks = {}; */

private:
	float cam_pov = M_PI / 2;
	float rayLineDist(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3);
	float outerRayIntersect(sf::Vector2f ray_pos, sf::Vector2f ray_end);
	float innerRayIntersect(sf::Vector2f ray_pos, sf::Vector2f ray_end);
	float normalizeAngle(float x)
	{
		x = fmod(x + M_PI, 2 * M_PI);
		if (x < 0) x += 2 * M_PI;
		return x - M_PI;
	}
};
