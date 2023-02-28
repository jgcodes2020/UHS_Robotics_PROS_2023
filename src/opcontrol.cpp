#include "lib/math.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"

#include "../include/selection.h"
#include "globals/globals.hpp"
#include "lib/robot.hpp"
#include "pros/rtos.hpp"
#include "route/route.hpp"

// if true, the robot drives backwards.
bool drive_rev = false;
bool ind_state = false;

static inline void movement() {
  // drivetrain
  drive_rev =
    (drive_rev || robot::rdbtn(DIGITAL_B)) && !robot::rdbtn(DIGITAL_X);
  robot::drive(
    robot::rdctrl(ANALOG_LEFT_Y), robot::rdctrl(ANALOG_RIGHT_X), drive_rev
  );
  // flywheel
  // motors_fw.move_velocity(robot::ctrl_bidi(600, DIGITAL_R1, DIGITAL_R2));
  // indexer
  if (robot::rdctrl(DIGITAL_DOWN))
    motor_ind.move_absolute(0.25, GREEN_RPM);
  else
    motor_ind.move_absolute(0, GREEN_RPM);
  // intake
  motors_itk.move_velocity(robot::ctrl_bidi(200, DIGITAL_L1, DIGITAL_L2));
  // expander
  adi_exp.set_value(robot::rdctrl(DIGITAL_LEFT));
}

// Runs during the driver control phase of the competition
// Also the default if no competition switch is available
void opcontrol() {
  adi_exp.set_value(LOW);
  motor_ind.tare_position();
  while (true) {
    movement();
  }
}
