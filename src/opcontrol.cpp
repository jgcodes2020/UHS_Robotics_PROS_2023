#include "main.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"

#include "../include/selection.h"
#include "globals/globals.hpp"
#include "lib/robot.hpp"
#include "pros/rtos.hpp"
#include "route/route.hpp"

enum rt_select_t { RT_INTAKE = 0, RT_INDEXER, RT_MAX };
int rt_mode = RT_INTAKE;

static inline void movement() {
  // drivetrain
  robot::drive(ANALOG_LEFT_Y, ANALOG_RIGHT_X);
  // flywheel
  motors_fw.move_velocity(robot::ctrl_bidi(600, DIGITAL_L1, DIGITAL_L2));
  
  // RT mode switching
  if (robot::switch_rt_mode()) {
    if (++rt_mode == RT_MAX)
      rt_mode = 0;
  }
  // RT controls
  switch (rt_mode) {
  case RT_INTAKE: {
    motor_itk.move_velocity(robot::ctrl_bidi(200, DIGITAL_R1, DIGITAL_R2));
    motor_itk.move_velocity(0);
  } break;
  case RT_INDEXER: {
    motor_itk.move_velocity(0);
    motor_ind.move_velocity(robot::ctrl_bidi(200, DIGITAL_R1, DIGITAL_R2));
  } break;
  }
  // expander
  adi_exp.set_value(ctrl.get_digital(DIGITAL_LEFT));
}

// Runs during the driver control phase of the competition
// Also the default if no competition switch is available
void opcontrol() {
  adi_exp.set_value(LOW);
  while (true) {
    movement();
  }
}
