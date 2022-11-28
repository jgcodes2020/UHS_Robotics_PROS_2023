#ifndef GLOBALS_HPP_INCLUDED
#define GLOBALS_HPP_INCLUDED

#include "main.h"
#include "pros/adi.h"
#include "pros/misc.h"
#include "pros/motors.h"

extern pros::Controller ctrl;

extern pros::IMU imu;

extern pros::Motor motor_fl;
extern pros::Motor motor_fr;
extern pros::Motor motor_bl;
extern pros::Motor motor_br;

extern pros::Motor motor_it;
extern pros::Motor motor_id;

extern pros::Motor motor_fwa;
extern pros::Motor motor_fwb;
extern pros::MotorGroup motor_fw;
#endif