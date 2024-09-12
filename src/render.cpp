#include "render.h"

#include <cmath>
#include <cstdio>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/System/Vector2.hpp"

void rectOutline(sf::Vector2f tl, sf::Vector2f size, float outline, sf::Color color)
{
    if (window == nullptr) {
        return;
    }

    sf::RectangleShape rect(sf::Vector2f(size.x, -size.y));
    rect.setPosition(tl.x, -tl.y);
    rect.setFillColor(sf::Color(0, 0, 0, 0));
    rect.setOutlineColor(color);
    rect.setOutlineThickness(outline);

    window->draw(rect);
}

void rectFill(sf::Vector2f tl, sf::Vector2f size, sf::Color color, float angle, bool centered)
{
    if (window == nullptr) {
        return;
    }

    sf::RectangleShape rect(sf::Vector2f(size.x, -size.y));
    if (centered) {
        rect.setOrigin(size.x / 2, -size.y / 2);
    }
    rect.setPosition(tl.x, -tl.y);
    rect.setRotation(-angle * (360 / (2 * M_PI)));
    rect.setFillColor(color);

    window->draw(rect);
}
void circle(sf::Vector2f pos, float radius, sf::Color color)
{
    if (window == nullptr) {
        return;
    }

    sf::CircleShape circ(radius);
    circ.setOrigin(radius, radius);
    circ.setPosition(pos.x, -pos.y);
    circ.setFillColor(color);

    window->draw(circ);
}
void line(sf::Vector2f p1, sf::Vector2f p2, sf::Color color)
{
    if (window == nullptr) {
        return;
    }

    p1.y *= -1;
    p2.y *= -1;

    sf::Vertex v1(p1);
    v1.color = color;

    sf::Vertex v2(p2);
    v2.color = color;
    sf::Vertex line[] = { v1, v2 };

    window->draw(line, 2, sf::Lines);
}

sf::RenderWindow* window = nullptr;
