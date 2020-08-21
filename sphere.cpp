#include "sphere.h"

namespace Tracer {
std::pair<bool, Vector3> Sphere::intersects(const Vector3& point,
                                            const Vector3& dir) const {
  Vector3 diff = point - center_position;
  float dot_product = dir.dot(diff);
  float delta = (std::pow(dot_product, 2)) -
                (diff.magnitude_squared() - std::pow(radius, 2));
  if (delta < 0) {
    return {false, Vector3(0, 0, 0)};
  }
  // we assume that the sphere is not behind you, therefore distance we are
  // looking for is the (-) delta, not (+) delta (the more negative side of the
  // sphere)
  float d = -dot_product - sqrt(delta);
  assert(d >= 0);
  return {true, point + dir * d};
}

Vector3 Sphere::get_normal(const Vector3& point) const {
    auto normal = point - center_position;
    normal.normalize();
  return normal;
}
}  // namespace Tracer