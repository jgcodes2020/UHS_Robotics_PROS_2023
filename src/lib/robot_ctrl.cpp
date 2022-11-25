#include "robot_ctrl.hpp"

#include "../globals/globals.hpp"
#include "main.h"
#include <cmath>

static const double sqrt2_2 = std::sqrt(2) / 2;

static int joymap(int x, int max) {
  return x * max / 128;
}

void xdrive_move(int x, int y, int r) {
  x = joymap(x, 200);
  y = joymap(y, 200);
  r = joymap(r, 200);
  
  motor_fl.move_velocity(+x + y + r);
  motor_fr.move_velocity(+x - y + r);
  motor_bl.move_velocity(-x + y + r);
  motor_br.move_velocity(-x - y + r);
}

void indexer() {
  // dist
  constexpr int dist = 5;
  
  motor_id.move_relative(dist, 127);
  motor_id.move_relative(-dist, 127);
}