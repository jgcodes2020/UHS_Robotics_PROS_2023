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

constexpr int32_t RED_RPM = 100;
constexpr int32_t GREEN_RPM = 200;
constexpr int32_t BLUE_RPM = 600;

#endif