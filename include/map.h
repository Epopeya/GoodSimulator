#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

void renderMap(sf::RenderWindow* window);
float getRayIntersect(sf::Vector2f ray_pos, float ray_angle);
float rayLineDist(sf::Vector2f ray_pos, float angle, sf::Vector2f p1, sf::Vector2f p2);
