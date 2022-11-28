#ifndef AUTON_CTRL_HPP
#define AUTON_CTRL_HPP

#include "linalg.hpp"
#include <cstdint>

struct RobotMotion {
  Vec3 pos;
  Vec3 vel;
};

// Update the point using current IMU measurements.
void update_point(double t, RobotMotion& rm);

#endif