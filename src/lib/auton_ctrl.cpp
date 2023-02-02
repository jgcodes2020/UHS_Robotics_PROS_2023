#include "auton_ctrl.hpp"
#include "../globals/globals.hpp"
#include <cmath>

namespace auton {
  void move_dist(double dist, double theta, int32_t vel) {
    theta -= M_PI_4;
    
    const double st = std::sin(theta), ct = std::cos(theta);
    const double dx = dist * st, dy = dist * ct;
    const double vx = vel * st, vy = vel * ct;
    
    motor_fl.move_relative(dx, vx);
    motor_fr.move_relative(dy, vy);
    motor_bl.move_relative(dy, vy);
    motor_br.move_relative(dx, vx);
    
    while (
      motor_fl.get_actual_velocity() != 0 || 
      motor_fr.get_actual_velocity() != 0 ||
      motor_bl.get_actual_velocity() != 0 ||
      motor_br.get_actual_velocity() != 0
      ) {
      pros::delay(10);
    }
  }
  
  void rotate_angle(double theta, double vel) {
    
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
  p.pos += p.vel * t + 0.5 * accel * (t*t);
  p.vel += accel * t;
}
