#include "globals.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"

pros::Controller ctrl(pros::E_CONTROLLER_MASTER);

// IMU
pros::IMU imu(2);

// left-front motor
pros::Motor motor_fl(7, MOTOR_GEAR_GREEN, false, MOTOR_ENCODER_ROTATIONS);
// right-front motor
pros::Motor motor_fr(9, MOTOR_GEAR_GREEN, true, MOTOR_ENCODER_ROTATIONS);
// left-back motor
pros::Motor motor_bl(8, MOTOR_GEAR_GREEN, false, MOTOR_ENCODER_ROTATIONS);
// right-back motor
pros::Motor motor_br(10, MOTOR_GEAR_GREEN, true, MOTOR_ENCODER_ROTATIONS);

pros::MotorGroup motors_l {motor_fl, motor_bl};
pros::MotorGroup motors_r {motor_fr, motor_br};

// intake
pros::Motor motor_itk(6, MOTOR_GEAR_GREEN, true, MOTOR_ENCODER_ROTATIONS);
// indexer
pros::Motor motor_ind(5, MOTOR_GEAR_GREEN, false, MOTOR_ENCODER_ROTATIONS);
// shooter
pros::Motor motor_fwa(4, MOTOR_GEAR_BLUE, true, MOTOR_ENCODER_ROTATIONS);
pros::Motor motor_fwb(3, MOTOR_GEAR_BLUE, true, MOTOR_ENCODER_ROTATIONS);
pros::MotorGroup motors_fw {motor_fwa, motor_fwb};

// expander
pros::ADIDigitalOut adi_exp(1, LOW);