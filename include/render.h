#pragma once

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

void rectOutline(
    sf::Vector2f top_left, sf::Vector2f size, float outline = 10, sf::Color color = sf::Color(255, 255, 255));
void rectFill(sf::Vector2f top_left, sf::Vector2f size, sf::Color color = sf::Color(255, 255, 255), float angle = 0,
    bool centered = false);
void circle(sf::Vector2f pos, float radius, sf::Color color = sf::Color(255, 255, 255));
void line(sf::Vector2f p1, sf::Vector2f p2, sf::Color color = sf::Color(255, 255, 255));

extern sf::RenderWindow* window; // WARN TODO this is global too
