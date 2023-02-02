#include "main.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"

#include "../include/selection.h"
#include "globals/globals.hpp"
#include "lib/auton_ctrl.hpp"
#include "lib/robot_ctrl.hpp"
#include "pros/rtos.hpp"
#include "route/route.hpp"

static double id_end_pos;
static constexpr double id_dist = 2;
static constexpr double id_tol = 0.25;

static inline void do_xdrive(pros::controller_analog_e_t stc_x, pros::controller_analog_e_t stc_y, pros::controller_analog_e_t stc_r) {
  xdrive_move(
    ctrl.get_analog(stc_x),
    ctrl.get_analog(stc_y),
    ctrl.get_analog(stc_r)
  );
}

static inline int32_t bit_enable(bool toggle, int32_t value) {
  return -int32_t(toggle) & value;
}

static inline int32_t reversible(int32_t x, pros::controller_digital_e_t btn, pros::controller_digital_e_t rev) {
  int32_t val = -int32_t(ctrl.get_digital(btn)) & x;
  int32_t tmp2 = ctrl.get_digital(rev);
  
  return (val ^ (-tmp2)) + tmp2;
}

static inline void movement() {
  do_xdrive(ANALOG_LEFT_X, ANALOG_LEFT_Y, ANALOG_RIGHT_X);
  
  // flywheel
  motor_fw.move_velocity(reversible(-600, DIGITAL_L1, DIGITAL_R1));
  
  // indexer
  if (ctrl.get_digital(DIGITAL_Y) && motor_id.get_position() < -id_tol) {
    motor_id.move_velocity(200);
  }
  else if (!ctrl.get_digital(DIGITAL_Y) && motor_id.get_position() > -id_dist + id_tol) {
    motor_id.move_velocity(-200);
  }
  else {
    motor_id.brake();
  }
  ctrl.print(0, 0, "IND: %2.3f", motor_id.get_position());
  
  // intake
  motor_it.move_velocity(reversible(200, DIGITAL_B, DIGITAL_R1));
}

// Runs during the driver control phase of the competition
// Also the default if no competition switch is available
void opcontrol() {
  // while (true) {
  //   movement();
  // }
  autonomous();
}
 