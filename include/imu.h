#include "robot.h"

class Imu {
public:
    Imu();
    void setup();
    int update();
    float rotation = 0;
};
