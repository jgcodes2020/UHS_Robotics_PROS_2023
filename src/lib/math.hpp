#ifndef MATH_HPP
#define MATH_HPP
#include <cmath>
#include <cstdint>

// reduce degree angle, unsigned
inline double reduce_deg_u(double x) {
  return fmod(x, 360) + ((x < 0)? 360 : 0);
}
// reduce degree angle, signed
inline double reduce_deg(double x) {
  return fmod(x, 360) + ((x < 0)? 180 : -180);
}
// signum function. 1 for x > 0, -1 for x < 0, 0 for x == 0
inline int32_t sgn(int32_t x) {
  return (x >> 31) | (x != 0);
}
// conditional negate. if b is true, -x, else x
inline int32_t cneg(int32_t x, bool b) {
  int32_t b2 = -((int32_t) b);
  return (x ^ b2) - b2;
}

constexpr int32_t RED_RPM = 100;
constexpr int32_t GREEN_RPM = 200;
constexpr int32_t BLUE_RPM = 600;

#endif