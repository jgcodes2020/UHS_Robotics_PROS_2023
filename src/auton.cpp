#include "lib/auton_ctrl.hpp"
#include "main.h"
void autonomous() {
  auton::move_dist(3, 0);
  auton::move_dist(3, M_PI);
}