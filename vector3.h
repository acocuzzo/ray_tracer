#ifndef VECTOR_3_H_
#define VECTOR_3_H_

#include <math.h>

namespace Tracer {

struct Vector3 {
  Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

  Vector3 operator-(const Vector3& rhs) const {
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
  }

  Vector3 operator+(const Vector3& rhs) const {
    return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
  }

  Vector3 operator*(float scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
  }

  Vector3& operator+=(const Vector3& rhs) {
      x += rhs.x;
      y += rhs.y;
      z += rhs.z;
      return *this; 
      }


  float dot(const Vector3& rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }

  Vector3 cross_product(const Vector3& rhs) const {
      return Vector3(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
  }

  float magnitude_squared() const { return x * x + y * y + z * z; }

  float magnitude() const { return std::sqrt(magnitude_squared()); }

  void normalize() {
    const float size = magnitude();
    x /= size;
    y /= size;
    z /= size;
  }

bool closer_to_screen_than(const Vector3& rhs){
    return z < rhs.z;
}
static Vector3 get_direction_vector(const Vector3& start, const Vector3& end) {
  Vector3 diff = end - start;
  diff.normalize();
  return diff;
}
static float get_distance_squared(const Vector3& start, const Vector3& end) {
  Vector3 diff = end - start;
  return diff.magnitude_squared();
}
static Vector3 Up() { return Vector3(0, 1, 0); }

static Vector3 Forward() { return Vector3(0, 0, 1); }

static Vector3 Right() { return Vector3(1, 0, 0); }


  float x;
  float y;
  float z;
};


}  // namespace Tracer
#endif