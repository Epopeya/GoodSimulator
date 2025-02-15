#include "slave.h"

// Global variable definitions
int last_encoder_read = 0;

block_t red_block = { .in_scene = false, .x = -1, .y = -1 };
block_t green_block = { .in_scene = false, .x = -1, .y = -1 };
float battery = 8.2f;

// Function definitions
void slaveSetup()
{
    printf("Slave setup completed!\n");
}

void servoAngle(float angle)
{
    robot.servo_angle = angle;
}

void motorSpeed(int speed)
{
    printf("setting motorspeed to: %i\n", speed);
    robot.motor_speed = speed * 0.1;
}

int getEncoders()
{
    int enc = robot.total_encoders - last_encoder_read;
    last_encoder_read = robot.total_encoders;
    return enc;
}

void slaveProcessSerial()
{
    left_distance = robot.left_dist;
    right_distance = robot.right_dist;
    front_distance = robot.front_dist;

    red_block.in_scene = false;
    green_block.in_scene = false;

    if (robot.blocks.x != 0) {
        red_block.in_scene = true;
    }
    if (robot.blocks.y != 0) {
        green_block.in_scene = true;
    }
}
