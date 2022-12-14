#include "main.h"
#include "pros/motors.hpp"

#include "../include/selection.h"
#include "globals/globals.hpp"
#include "route/route.hpp"
#include "lib/auton_ctrl.hpp"
#include "lib/robot_ctrl.hpp"

// LLEMU center button, idk what this is for
void on_center_button() {
}

// Sort of like main()
void initialize() {
  selectorInit();
}

// Runs when comp switch is in "disabled"
void disabled() {}

// Post-init, runs before autonomous() when competition switch is there
void competition_initialize() {}

// Runs during the autonomous phase of the competition
void autonomous() {}