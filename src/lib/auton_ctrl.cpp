#include "auton_ctrl.hpp"
#include "../globals/globals.hpp"



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
