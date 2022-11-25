#include "globals.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"

pros::Controller ctrl(pros::E_CONTROLLER_MASTER);

// left-front motor
pros::Motor motor_fl(20, MOTOR_GEAR_GREEN, false, MOTOR_ENCODER_ROTATIONS);
// right-front motor
pros::Motor motor_fr(11, MOTOR_GEAR_GREEN, false, MOTOR_ENCODER_ROTATIONS);
// left-back motor
pros::Motor motor_bl(10, MOTOR_GEAR_GREEN, false, MOTOR_ENCODER_ROTATIONS);
// right-back motor
pros::Motor motor_br(1, MOTOR_GEAR_GREEN, false, MOTOR_ENCODER_ROTATIONS);

// intake
pros::Motor motor_it(3, MOTOR_GEAR_GREEN, false, MOTOR_ENCODER_ROTATIONS);
// indexer
pros::Motor motor_id(6, MOTOR_GEAR_GREEN, false, MOTOR_ENCODER_ROTATIONS);
// shooter
pros::Motor motor_fwa(7, MOTOR_GEAR_BLUE, false, MOTOR_ENCODER_ROTATIONS);
pros::Motor motor_fwb(8, MOTOR_GEAR_BLUE, false, MOTOR_ENCODER_ROTATIONS);
pros::MotorGroup motor_fw({motor_fwa, motor_fwb});