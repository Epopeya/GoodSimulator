#include "robot.h"

#include <cmath>

#include "SFML/System/Vector2.hpp"
#include "map.h"
#include "math.h"
#include "render.h"

robotSimulation::robotSimulation(sf::Vector2f start_pos, float start_angle)
    : pos(start_pos)
    , angle(start_angle)
{
    updateMapData();
}

void robotSimulation::update()
{
    updateMapData();

    // servo imu
    servo_angle = fmin(fmax(servo_angle, -M_PI / 4), M_PI / 4);
    imu_angle += (servo_angle * servo_speed);

    // encoders
    cum_dist += motor_speed / encoder_to_mm;
    int encoder_diff = floor(cum_dist);
    cum_dist -= encoder_diff;
    total_encoders += encoder_diff;

    // movement
    sf::Vector2f direction_vector = sf::Vector2f(cos(angle), sin(angle));
    direction_vector = direction_vector * motor_speed;

    angle += (servo_angle * servo_speed);
    pos += direction_vector;
}

void robotSimulation::updateMapData()
{
    left_dist = map.getRayIntersect(pos, angle + (M_PI / 2));
    front_dist = map.getRayIntersect(pos, angle) - 150;
    right_dist = map.getRayIntersect(pos, angle - (M_PI / 2));

    blocks = map.getVisibleBlocks(pos, angle, cam_fov);
}

void robotSimulation::render()
{
    map.render();

    float left_angle = (angle + M_PI / 2);
    float front_angle = (angle);
    float right_angle = (angle - M_PI / 2);

    sf::Vector2f p0 = pos + sf::Vector2f(cos(left_angle), sin(left_angle)) * left_dist;
    sf::Vector2f p1 = pos + sf::Vector2f(cos(front_angle), sin(front_angle)) * front_dist;
    sf::Vector2f p2 = pos + sf::Vector2f(cos(right_angle), sin(right_angle)) * right_dist;

    line(pos, p0);
    line(pos, p1);
    line(pos, p2);

    rectFill(pos, sf::Vector2f(300, 200), sf::Color(255, 255, 255), angle, true);

    circle(pos, 25, sf::Color(255, 0, 0));
}

// main robot
robotSimulation robot = robotSimulation(sf::Vector2f(1500, 500), 0);
