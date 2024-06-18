#include <Arduino.h>
#include <debug.h>
#include <geometry.h>
#include <imu.h>
#include <lidar.h>
#include <math.h>
#include <pid.h>
#include <slave.h>
#include <timer.h>

/* #define SIMULATE_MOVEMENT */

PID servoPid(0.5f, 0.08f, 0.35f);
Imu imu;
Timer nav_timer(20);

#define ENCODERS_TO_MM 1.6f
vector2_t position = {.x = 0, .y = 0};
void updatePosition(vector2_t* pos, float angle, int encoders)
{
	pos->x += encoders * cos(angle) * ENCODERS_TO_MM;
	pos->y += encoders * sin(angle) * ENCODERS_TO_MM;
	debug_position(*pos);
}

#define ERROR_COEFICENT 0.005f
#define ANGLE_CONSTRAINT PI / 3
float angleToAxis(float from, float to)
{
	float angle = (to - from) * ERROR_COEFICENT;
	return constrain(angle, -ANGLE_CONSTRAINT, ANGLE_CONSTRAINT);
}

int turn_count = 0;

#define BLOCK_FIXED_OFFSET 250
#define MIN_AFTER_DISTANCE 200
float last_block = 0; // last recorded position of the block
float cam_offset = 0;
void camOffsetGood(int zone)
{
	float pos = (turn_count % 2) ? position.y : position.x;
	if (green_block.in_scene)
	{
		if (cam_offset == 0) { debug_msg("green block"); }
		cam_offset = BLOCK_FIXED_OFFSET; // left
		last_block = pos;
	}
	else if (red_block.in_scene)
	{
		if (cam_offset == 0) { debug_msg("red block"); }
		cam_offset = -BLOCK_FIXED_OFFSET; // right
		last_block = pos;
	}

	if (abs(last_block - pos) > MIN_AFTER_DISTANCE) { cam_offset = 0; }
}

int orientation = 0;
int last_zone = 0;
int zone = 0;
float zoneGood()
{
	float from = (turn_count % 2) ? position.x : position.y;
	float to = from;
	float sign = 0;

	if (position.y < 500 && position.y > -500 && position.x < 500)
	{
		to = 0;
		sign = 1;
		zone = 0;
	}
	else if (position.x > 500 && position.y < 1500 && position.y > -1500)
	{
		to = 1000;
		sign = -1 * orientation;
		zone = 1;
	}
	else if (position.x > -500 && (position.y > 1500 || position.y < -1500))
	{
		to = 2000 * orientation;
		sign = -1;
		zone = 2;
	}
	else if (position.x < -500 && (position.y > 500 || position.y < -500))
	{
		to = -1000;
		sign = 1 * orientation;
		zone = 3;
	}

	camOffsetGood(zone);
	to += cam_offset * sign * orientation;

	float angle = turn_count * (PI / 2) + (angleToAxis(from, to) * sign);

	if (zone != last_zone)
	{
		turn_count += orientation;
		cam_offset = 0;
		debug_msg("zone change to turn: %i 🦔", turn_count);
	}
	last_zone = zone;

	return angle;
}

float start_distance_y;
void setup()
{
	pinMode(33, INPUT_PULLUP);
	pinMode(26, OUTPUT);

	debug_init();
	slaveSetup();
	imu.setup();

	while (battery < 0.01f)
	{
		slaveProcessSerial();
	} // WARN
	debug_battery(battery);

	if (battery > 4)
	{
		lidarSetup();
		vector2_t start_distances = lidarInitialPosition();
		position.x = 1500 - start_distances.x;
		position.y = 500 - start_distances.y;
		start_distance_y = start_distances.y;
		lidarStart();
	}
	debug_msg("Setup completed");

	// wait for button
	digitalWrite(26, HIGH);
	while (digitalRead(33)) {}
	digitalWrite(26, LOW);
	delay(500);

	if (battery < 4) { motorSpeed(0); }
	else { motorSpeed(150); }

	servoPid.target = 0;
}

void loop()
{
	/* printf("pox x: %f, pos y: %f\n", position.x, position.y); */
	slaveProcessSerial();
	if (imu.update()) { debug_current_direction(imu.rotation); }

	if (nav_timer.primed())
	{
		updatePosition(&position, imu.rotation, getEncoders());

		// Initial Turn
		if (orientation == 0)
		{
			if (left_distance > 1500)
			{
				debug_msg("setting orientation to %i", orientation);
				orientation = 1;
				position.y = 500 - start_distance_y;
			}
			else if (right_distance > 1500)
			{
				debug_msg("setting orientation to %i", orientation);
				orientation = -1;
				position.y = start_distance_y - 500;
			}
		}
		// Standard Navigation
		else { servoPid.target = zoneGood(); }
		debug_target_direction(servoPid.target);
		servoAngle(servoPid.update(imu.rotation));
	}
}
