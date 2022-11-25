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

static bool shoot_state = false;

static inline void do_xdrive(pros::controller_analog_e_t stc_x, pros::controller_analog_e_t stc_y, pros::controller_analog_e_t stc_r) {
  xdrive_move(
    ctrl.get_analog(stc_x),
    ctrl.get_analog(stc_y),
    ctrl.get_analog(stc_r)
  );
}

static inline int32_t pair_buttons(pros::controller_digital_e_t btn_f, pros::controller_digital_e_t btn_b) {
  bool vf = ctrl.get_digital(btn_f), vb = ctrl.get_digital(btn_b);
  return 128 * int32_t(vf) - 128 * int32_t(vb);
}

static inline void movement() {
  do_xdrive(ANALOG_LEFT_X, ANALOG_LEFT_Y, ANALOG_RIGHT_X);
  
  // flywheel
  motor_fw.move_velocity(ctrl.get_digital(DIGITAL_L2)? -600 : 0);
  
  // indexer
  if (!shoot_state) {
    if (motor_id.get_position() <= 0.02) {
      if (ctrl.get_digital(DIGITAL_Y)) {
        shoot_state = true;
        motor_id.move_velocity(200);
      }
      else {
        motor_id.move_velocity(0);
      }
    }
    else {
      motor_id.move_velocity(-200);
    }
  }
  else {
    if (motor_id.get_position() >= 2.5) {
      shoot_state = false;
      motor_id.move_velocity(-200);
    }
    else {
      motor_id.move_velocity(200);
    }
  }
  
  // intake
  if (ctrl.get_digital(DIGITAL_B)) {
    if (ctrl.get_digital(DIGITAL_R1)) {
      motor_it.move_velocity(-200);
    }
    else {
      motor_it.move_velocity(200);
    }
  }
  else {
    motor_it.move_velocity(0);
  }
}

// Runs during the driver control phase of the competition
// Also the default if no competition switch is available
void opcontrol() {
  while (true) {
    movement();
  }
}
/*
GEAR TRAIN NOTES:

motors: 12
combine: 36
reduce: 80:64:12

80 / 24 = 10/3

*/
