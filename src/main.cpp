#include "main.h"
#include "pros/motors.hpp"

#include "../include/selection.h"
#include "globals/globals.hpp"
#include "pros/rtos.hpp"
#include "route/route.hpp"
#include "lib/robot_ctrl.hpp"

// LLEMU center button, idk what this is for
void on_center_button() {
}

// Run at the beginning of a competition
void initialize() {
  selectorInit();
  adi_exp.set_value(LOW);
  while (imu.is_calibrating()) {
    pros::delay(10);
  }
}

// Runs when comp switch is in "disabled"
void disabled() {}

// Post-init, runs before autonomous() when competition switch is there
void competition_initialize() {}
