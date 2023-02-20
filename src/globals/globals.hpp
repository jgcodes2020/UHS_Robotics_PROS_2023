#ifndef GLOBALS_HPP_INCLUDED
#define GLOBALS_HPP_INCLUDED

#include "main.h"
#include "okapi/api.hpp"
#include "pros/adi.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/motors.hpp"

extern pros::Controller ctrl;

extern pros::IMU imu;

extern pros::Motor motor_fl;
extern pros::Motor motor_fr;
extern pros::Motor motor_bl;
extern pros::Motor motor_br;

extern pros::MotorGroup motors_l;
extern pros::MotorGroup motors_r;

extern pros::Motor motor_itk;
extern pros::Motor motor_ind;

extern pros::Motor motor_fwa;
extern pros::Motor motor_fwb;
extern pros::MotorGroup motors_fw;

extern pros::ADIDigitalOut adi_exp;
#endif