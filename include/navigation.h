#pragma once
#ifndef NAVIGATION_H
#define NAVIGATION_H
#include "vector.h"

#define ERROR_COEFICENT 0.005f
#define ANGLE_CONSTRAINT PI / 3

class Axis {
public:
    Axis(Vector pos, int turn, int counter_clockwise, float target, float _end = 0.0f);

    // returns the target angle needed to follow the line
    float follow(Vector pos);
    float distanceTraveled(Vector pos);
    bool finished(Vector pos);

    void resetDistanceTraveled(Vector pos);
    void setEnd(Vector pos);

    void reverse(int _counter_clockwise);

    void print();

    int turn = 0; // most of the other vars come from turn
    int counter_clockwise;
    bool follow_y = false;
    int dir = 1;
    float target = 0;
    float distance_pos = 0; // used only for distance
    float start_pos = 0;
    float end_pos = 0;
};
#endif
