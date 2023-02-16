#include "lib/auton_ctrl.hpp"
#include "main.h"
void autonomous() {
  while (true) {
    auton::move_dist(3, 0);
    auton::move_dist(3, M_PI_2);
    auton::move_dist(3, M_PI);
    auton::move_dist(3, -M_PI_2);
  }
}