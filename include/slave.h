#pragma once
#include "Arduino.h"
#include "lidar.h"
#include "robot.h"

// Global variables and structures
extern int last_encoder_read;

typedef struct
{
    bool in_scene;
    int x;
    int y;
} block_t;

extern block_t red_block;
extern block_t green_block;
extern float battery;

// Function declarations
void slaveSetup();
void servoAngle(float angle);
void motorSpeed(int speed);
int getEncoders();
void slaveProcessSerial();
