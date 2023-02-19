#include "main.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"

#include "../include/selection.h"
#include "globals/globals.hpp"
#include "lib/robot.hpp"
#include "pros/rtos.hpp"
#include "route/route.hpp"

static double id_end_pos;
static constexpr double id_dist = 2;
static constexpr double id_tol = 0.25;



static inline void movement() {
  // drivetrain
  robot::drive(ANALOG_LEFT_Y, ANALOG_RIGHT_X);
  // flywheel
  motors_fw.move_velocity(robot::ctrl_bidi(-600, DIGITAL_L1, DIGITAL_L2));
  // indexer
  motor_ind.move_velocity(robot::ctrl_bidi(-200, DIGITAL_R1, DIGITAL_R2));
  // intake
  motor_it.move_velocity(robot::ctrl_bidi(200, DIGITAL_UP, DIGITAL_DOWN));
  // expander
  adi_exp.set_value(robot::all_buttons_down());
}

// Runs during the driver control phase of the competition
// Also the default if no competition switch is available
void opcontrol() {
  adi_exp.set_value(LOW);
  while (true) {
    movement();
  }
}
 