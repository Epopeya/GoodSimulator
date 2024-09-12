#include "map.h"

#include <cmath>
#include <cstdio>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "render.h"

Map::Map()
    : inner_rect(sf::Vector2f(1000, 1000)) // this scales upward... fuck
    , outer_rect(sf::Vector2f(3000, 3000))
{
    inner_rect.setPosition(1000, 1000);
    outer_rect.setPosition(0, 0);
}

float Map::getRayIntersect(sf::Vector2f ray_pos, float ray_angle)
{
    sf::Vector2f ray_end = ray_pos + sf::Vector2f(cos(ray_angle), sin(ray_angle)) * 500000.0f;
    return getRayIntersect(ray_pos, ray_end);
}

float Map::getRayIntersect(sf::Vector2f ray_pos, sf::Vector2f ray_end)
{
    return fmin(outerRayIntersect(ray_pos, ray_end), innerRayIntersect(ray_pos, ray_end));
}

// TODO: this fails sometimes around 180 / -180 degrees, and rendering should me moved somewhere else
sf::Vector2i Map::getVisibleBlocks(sf::Vector2f pos, float angle, float fov)
{
    sf::Vector2i out_blocks(0, 0); // red, green
    float norm_angle = normalizeAngle(angle);

    for (sf::Vector2f block_pos : red_blocks) {
        sf::Vector2f block_dir = block_pos - pos;
        float block_angle = std::atan2(block_dir.y, block_dir.x) - norm_angle;
        float dist = innerRayIntersect(pos, block_pos);
        if (block_angle > -fov && block_angle < fov && dist > 5000) {
            line(pos, block_pos, sf::Color(255, 0, 0));
            out_blocks.x++;
        }
    }

    for (sf::Vector2f block_pos : green_blocks) {
        sf::Vector2f block_dir = block_pos - pos;
        float block_angle = std::atan2(block_dir.y, block_dir.x) - norm_angle;
        float dist = innerRayIntersect(pos, block_pos);
        if (block_angle > -fov && block_angle < fov && dist > 5000) {
            line(pos, block_pos, sf::Color(0, 255, 0));
            out_blocks.y++;
        }
    }
    return out_blocks;
}

void Map::render()
{
    rectFill(inner_rect.getPosition(), inner_rect.getSize(), sf::Color(150, 150, 150));
    rectOutline(outer_rect.getPosition(), outer_rect.getSize(), 100, sf::Color(150, 150, 150));

    for (sf::Vector2f p : red_blocks) {
        rectFill(p, sf::Vector2f(50, 50), sf::Color(255, 0, 0), 0, true);
    }
    for (sf::Vector2f p : green_blocks) {
        rectFill(p, sf::Vector2f(50, 50), sf::Color(0, 255, 0), 0, true);
    }
}

float Map::rayLineDist(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3)
{
    sf::Vector2f s1 = p1 - p0;
    sf::Vector2f s2 = p3 - p2;

    float s, t;
    s = (-s1.y * (p0.x - p2.x) + s1.x * (p0.y - p2.y)) / (-s2.x * s1.y + s1.x * s2.y);
    t = (s2.x * (p0.y - p2.y) - s2.y * (p0.x - p2.x)) / (-s2.x * s1.y + s1.x * s2.y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
        sf::Vector2f inter = p0 + (t * s1);
        sf::Vector2f dist = inter - p0;
        // Collision detected
        return std::sqrt(dist.x * dist.x + dist.y * dist.y);
    }

    return 50000; // No collision
}

float Map::outerRayIntersect(sf::Vector2f ray_pos, sf::Vector2f ray_end)
{
    float dist = 100000;

    sf::Vector2f p0 = outer_rect.getTransform().transformPoint(outer_rect.getPoint(0));
    sf::Vector2f p1 = outer_rect.getTransform().transformPoint(outer_rect.getPoint(1));
    sf::Vector2f p2 = outer_rect.getTransform().transformPoint(outer_rect.getPoint(2));
    sf::Vector2f p3 = outer_rect.getTransform().transformPoint(outer_rect.getPoint(3));

    dist = fmin(rayLineDist(ray_pos, ray_end, p0, p1), dist);
    dist = fmin(rayLineDist(ray_pos, ray_end, p1, p2), dist);
    dist = fmin(rayLineDist(ray_pos, ray_end, p2, p3), dist);
    dist = fmin(rayLineDist(ray_pos, ray_end, p3, p0), dist);

    return dist;
}

float Map::innerRayIntersect(sf::Vector2f ray_pos, sf::Vector2f ray_end)
{
    float dist = 100000;

    sf::Vector2f q0 = inner_rect.getTransform().transformPoint(inner_rect.getPoint(0));
    sf::Vector2f q1 = inner_rect.getTransform().transformPoint(inner_rect.getPoint(1));
    sf::Vector2f q2 = inner_rect.getTransform().transformPoint(inner_rect.getPoint(2));
    sf::Vector2f q3 = inner_rect.getTransform().transformPoint(inner_rect.getPoint(3));

    dist = fmin(rayLineDist(ray_pos, ray_end, q0, q1), dist);
    dist = fmin(rayLineDist(ray_pos, ray_end, q1, q2), dist);
    dist = fmin(rayLineDist(ray_pos, ray_end, q2, q3), dist);
    dist = fmin(rayLineDist(ray_pos, ray_end, q3, q0), dist);

    return dist;
}
