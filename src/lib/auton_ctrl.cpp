#include "auton_ctrl.hpp"
#include "../globals/globals.hpp"
#include <cmath>

namespace auton {
  static void xdrive_await_stop() {
    constexpr double max_err = 0.5;
    while (
      fabs(motor_fl.get_actual_velocity()) > max_err || 
      fabs(motor_fr.get_actual_velocity()) > max_err ||
      fabs(motor_bl.get_actual_velocity()) > max_err ||
      fabs(motor_br.get_actual_velocity()) > max_err
      ) {
      pros::delay(10);
    }
  }
  
  void xdrive_slide_dist(double dist, double theta, double vel) {
    theta -= M_PI_4;
    // adjust this constant as necessary
    dist *= 1;
    
    // sin/cos of theta
    const double st = std::sin(theta), ct = std::cos(theta);
    const double dx = dist * st, dy = dist * ct;
    const double vx = vel * st, vy = vel * ct;
    
    // pros::lcd::print(0, "dx: %2.4f | dy: %2.4f", dx, dy);
    // pros::lcd::print(1, "vx: %2.4f | vy: %2.4f", vx, vy);
    
    ctrl.print(0, 0, "dx: %2.4f | dy: %2.4f | vx: %2.4f | vy: %2.4f", dx, dy, vx, vy);
    
    motor_fl.move_velocity(0);
    motor_fr.move_velocity(0);
    motor_bl.move_velocity(0);
    motor_br.move_velocity(0);
    auton::xdrive_await_stop();
    
    motor_fl.move_relative(dx, vx);
    motor_fr.move_relative(-dy, vy);
    motor_bl.move_relative(dy, vy);
    motor_br.move_relative(-dx, vx);
    auton::xdrive_await_stop();
    
  }
  
  void rotate_angle(double theta, double vel) {
    // adjust this constant as necessary
    theta *= 15.70796326794896619;
    
    motor_fl.move_velocity(0);
    motor_fr.move_velocity(0);
    motor_bl.move_velocity(0);
    motor_br.move_velocity(0);
    auton::xdrive_await_stop();
    
    motor_fl.move_relative(theta, vel);
    motor_fr.move_relative(theta, vel);
    motor_bl.move_relative(theta, vel);
    motor_br.move_relative(theta, vel);
    auton::xdrive_await_stop();
  }
}

void update_point(double t, RobotMotion &p) {
  auto accel_raw = imu.get_accel();
  auto quat_raw = imu.get_quaternion();
  
  auto accel = *(Vec3*) &accel_raw;
  auto quat = *(Quat*) &quat_raw;
  
  // convert from ms to s
  t /= 1000;
  
  // rotate the acceleration to its proper direction
  accel = rotate(accel, quat);
  
  // convert from g's to m/s
  accel /= 9.807;
  
  // execute kinematics
  // Δd = vt + (1/2)at^2 (note this is factored)
  p.pos += t * (p.vel + 0.5 * accel * t);
  // Δv = at
  p.vel += t * accel;
}
