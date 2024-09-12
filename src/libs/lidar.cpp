#include "lidar.h"
#include "robot.h"

float front_distance = robot.front_dist;
float right_distance = robot.right_dist;
float left_distance = robot.left_dist;

// Function definitions
void lidarSetup() { }

std::vector<float> lidarInitialDistances()
{
    std::vector<float> out(3); // Initialize with size 3
    out[0] = robot.left_dist;
    out[1] = robot.right_dist;
    out[2] = robot.front_dist;
    return out;
}

void lidarStart() { }
