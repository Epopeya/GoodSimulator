#pragma once
#include "Arduino.h"
#include "lidar.h"
#include "robot.h"

int last_encoder_read = 0;

void slaveSetup()
{
	printf("Slave setup completed!\n");
};
void servoAngle(float angle)
{
	robot.servo_angle = angle;
};
void motorSpeed(int speed)
{
	printf("setting motorspeed to: %i\n", speed);
	robot.motor_speed = speed * 0.1;
};
int getEncoders()
{
	int enc = robot.total_encoders - last_encoder_read;
	last_encoder_read = robot.total_encoders;
	return enc;
};
void slaveProcessSerial() {
	left_distance = robot.left_dist;
	right_distance = robot.right_dist;
	front_distance = robot.front_dist;
};

typedef struct
{
	bool in_scene;
	int x;
	int y;
} block_t;

extern block_t red_block = {.in_scene = false, .x = -1, .y = -1};
extern block_t green_block = {.in_scene = false, .x = -1, .y = -1};
extern float battery = 8.2f;
