#ifndef AUTON_CTRL_HPP
#define AUTON_CTRL_HPP

#include "linalg.hpp"
#include <cstdint>

namespace auton {
  void init();
  void xdrive_slide_dist(double dist, double theta, double vel = 100);
}

struct RobotMotion {
  Vec3 pos;
  Vec3 vel;
};

// Update the point using current IMU measurements.
void update_point(double t, RobotMotion& rm);

#endif