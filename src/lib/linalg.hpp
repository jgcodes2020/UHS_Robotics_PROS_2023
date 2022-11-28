#ifndef LINALG_HPP
#define LINALG_HPP

struct Vec3 {
  double x, y, z;
};

struct Quat {
  double r, i, j, k;
};

inline Vec3 operator+(const Vec3& a, const Vec3& b) {
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}

inline Vec3& operator+=(Vec3& a, const Vec3& b) {
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  return a;
}

inline Vec3 operator-(const Vec3& a, const Vec3& b) {
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}

inline Vec3& operator-=(Vec3& a, const Vec3& b) {
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  return a;
}

inline Vec3 operator*(const Vec3& a, double b) {
  return {a.x * b, a.y * b, a.z * b};
}

inline Vec3 operator*(double a, const Vec3& b) {
  return b * a;
}

inline Vec3& operator*=(Vec3& a, double b) {
  a.x *= b;
  a.y *= b;
  a.z *= b;
  return a;
}

inline Vec3 operator/(const Vec3& a, double b) {
  return {a.x / b, a.y / b, a.z / b};
}

inline Vec3& operator/=(Vec3& a, double b) {
  a.x /= b;
  a.y /= b;
  a.z /= b;
  return a;
}

inline Quat operator*(const Quat& a, const Quat& b) {
  return Quat {
    a.r * b.r - a.i * b.i - a.j * b.j - a.k * b.k,
    a.r * b.i + a.i * b.r + a.j * b.k - a.k * b.j,
    a.r * b.j - a.i * b.k + a.j * b.r + a.k * b.i,
    a.r * b.k - a.i * b.j + a.j * b.i + a.k * b.r,
  };
}

inline Quat conj(const Quat& a) {
  return {a.r, -a.i, -a.j, -a.k};
}

inline Vec3 rotate(const Vec3& a, const Quat& b) {
  Quat inv_b = conj(b);
  Quat q_a {0, a.x, a.y, a.z};
  Quat res = b * q_a * inv_b;
  
  return {res.i, res.j, res.k};
}

#endif