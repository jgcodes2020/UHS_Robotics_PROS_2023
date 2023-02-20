#ifndef AUTON_HPP
#define AUTON_HPP

#include <cmath>
#include "../globals/globals.hpp"
#include "math.hpp"
#include "pros/rtos.hpp"

namespace auton {
  // Tolerance when waiting for a motor to stop.
  constexpr double stop_tol = 10;
  // wheel circumference * gear ratio.
  constexpr double slide_mult = (5.0 * M_PI) * (1);
  // number of turns of leniency in position.
  constexpr double slide_tol = 0.75 / slide_mult;
  // min threshold for rotation.
  constexpr double rotate_tmin = 10;
  // max threshold for rotation.
  constexpr double rotate_tmax = 100;
  // (* 10ms) how long to wait to ensure flywheel is stably at speed.
  constexpr int32_t fw_timer_len = 30;
  // rack gear ratio for indexer.
  constexpr double index_mult = 12 * 2.5 / 19.0;
  // tolerance on indexer movement.
  constexpr double index_tol = 0.1 / index_mult;
  // distance to slide the indexer.
  constexpr double index_dist = 1.0 / index_mult;

  inline bool within_pos_tol(pros::Motor& mt, double tol) {
    return fabs(mt.get_position() - mt.get_target_position()) <= tol;
  }
  inline bool is_stopped(pros::Motor& mt) {
    return fabs(mt.get_actual_velocity()) > stop_tol;
  }
  
  inline void stop() {
    motors_l.move_velocity(0);
    motors_r.move_velocity(0);
    while (!(is_stopped(motor_fl) && is_stopped(motor_fr))) {
      pros::delay(10);
    }
  }
  
  // Moves for a specific amount of time.
  // time: time to move for
  // vel: velocity to move at.
  inline void slide_time(int32_t time, double vel = 170) {
    motors_l.move_velocity(vel);
    motors_r.move_velocity(vel);
    pros::delay(time);
    stop();
  }
  
  // Rotates for a specific amount of time.
  // time: time to move for
  // vel: velocity to move at. + -> CW, - -> CCW
  inline void rotate_time(int32_t time, double vel) {
    motors_l.move_velocity(vel);
    motors_r.move_velocity(-vel);
    pros::delay(time);
    stop();
  }

  // Moves a given distance, using the motor encoders.
  // dist: distance to move, in inches
  // vel: maximum velocity to move at.
  inline void slide_dist(double dist, double vel = 170) {
    motors_l.move_relative(dist / slide_mult, vel);
    motors_r.move_relative(dist / slide_mult, vel);

    while (!(
      within_pos_tol(motor_fl, slide_tol) && within_pos_tol(motor_fr, slide_tol)
    )) {
      pros::delay(10);
    }
  }

  // Rotates to a given heading, based on IMU.
  // tdst: angle to move to, in degrees
  // mult: multiplier that affects velocity.
  inline void rotate_to(double tdst, double mult = 0.6) {
    double tcur, tdiff, vel;
    // init loop
    tdst = reduce_deg_u(tdst);
    tcur = imu.get_heading();
    // loop until threshold.
    while (fabs(tdst - tcur) > rotate_tmin) {
      tcur = imu.get_heading();
      // Davis's formula
      tdiff = fmin(1.0, reduce_deg(tdst - tcur) / rotate_tmax);
      vel   = tdiff * mult * GREEN_RPM;
      // Turn
      motors_l.move_velocity(vel);
      motors_r.move_velocity(-vel);
    }
    stop();
  }

  // Starts or stops the flywheel.
  // state: if true, starts the flywheel, otherwise stops it.
  inline void set_flywheel(bool state) {
    // bit hacking: false = 0, true = 600
    motors_fw.move_velocity(-((int32_t) state) & BLUE_RPM);
  }

  // Waits for the flywheel to spin up.
  // spd: the threshold to pass.
  // timer_len: time (in 10ms increments) to wait for speed to stabilize.
  inline void await_flywheel(double spd, double timer_len = fw_timer_len) {
    int32_t timer = timer_len;
    do {
      if (fabs(motor_fwa.get_actual_velocity()) < spd)
        --timer;
      else if (timer < timer_len)
        ++timer;
    } while (timer > 0);
  }

  // Fires the indexer.
  inline void indexer_once() {
    double curr_pos = motor_ind.get_position();
    motor_ind.move_relative(index_dist, 200);
    while (!within_pos_tol(motor_ind, index_tol)) {
      pros::delay(10);
    }
    motor_ind.move_absolute(curr_pos, 200);
    while (!within_pos_tol(motor_ind, index_tol)) {
      pros::delay(10);
    }
  }

  // Starts or stops the intake.
  // state: 1, 0, or -1 (forward, stopped, backwards)
  inline void set_intake(int32_t state) {
    motor_itk.move_velocity(state * GREEN_RPM);
  }
}  // namespace auton

#endif