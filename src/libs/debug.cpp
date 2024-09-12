#include "debug.h"

#include <stdarg.h>
#include <stdio.h>

// Function definitions
void debug_init()
{
}

void debug_msg(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\n");
}

void debug_target_direction(float angle)
{
}

void debug_current_direction(float angle)
{
}

void debug_battery(float voltage)
{
}

void debug_position(Vector pos)
{
}

void debug_waypoints(Vector waypoints[], size_t waypoints_len)
{
}

void debug_lidar(Vector pos)
{
}

void debug_map_flip(bool flipped)
{
}
