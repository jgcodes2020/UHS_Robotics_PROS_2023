#ifndef ROBOT_CTRL_HPP
#define ROBOT_CTRL_HPP

#include "../globals/globals.hpp"
#include "main.h"

namespace robot {
inline int32_t joymap(int32_t x, int32_t max) { return x * max / 128; }

inline void drive(pros::controller_analog_e_t js,
                  pros::controller_analog_e_t jr) {
  int spd = joymap(ctrl.get_analog(js), 200);
  int rot = joymap(ctrl.get_analog(jr), 200);

  motors_l.move_velocity(std::clamp(spd + rot, -200, 200));
  motors_r.move_velocity(std::clamp(spd - rot, -200, 200));
}

// Control mapping: press btn to go forward, rev to reverse. If both pressed,
// nothing happens. This simply uses bit hacking to do it faster.
static inline int32_t ctrl_bidi(int32_t x, pros::controller_digital_e_t fwd,
                                pros::controller_digital_e_t rev) {
  int32_t f = -ctrl.get_digital(fwd), r = -ctrl.get_digital(rev);
  return (x & f) + (-x & r);
}
// Checks whether ALL 8 buttons are pressed.
static inline int32_t all_buttons_down() {
  return ctrl.get_digital(DIGITAL_UP) && ctrl.get_digital(DIGITAL_DOWN) &&
         ctrl.get_digital(DIGITAL_LEFT) && ctrl.get_digital(DIGITAL_RIGHT) &&
         ctrl.get_digital(DIGITAL_A) && ctrl.get_digital(DIGITAL_B) &
         ctrl.get_digital(DIGITAL_X) && ctrl.get_digital(DIGITAL_Y);
}
} // namespace robot

#endif