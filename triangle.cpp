#include "triangle.h"

#include "light.h"
#include "material.h"

namespace Tracer {
std::pair<bool, Vector3> Triangle::intersects(const Vector3& origin,
                                              const Vector3& dv) const {
  const float epsilon = 0.000001;
  Vector3 edge1 = vertex1 - vertex0;
  Vector3 edge2 = vertex2 - vertex0;
  Vector3 h = dv.cross_product(edge2);
  float a = edge1.dot(h);
  // ray is parallel to this triangle
  if (a > -epsilon && a < epsilon) {
    return {false, Vector3(0, 0, 0)};
  }
  float f = 1.0 / a;
  Vector3 s = origin - vertex0;
  float u = f * s.dot(h);
  if (u < 0.0 || u > 1.0) {
    return {false, Vector3(0, 0, 0)};
  }
  Vector3 q = s.cross_product(edge1);
  float v = f * dv.dot(q);
  if (v < 0.0 || u + v > 1.0) {
    return {false, Vector3(0, 0, 0)};
  }
  // find intersection point:
  float t = f * edge2.dot(q);
  if (t > epsilon) {  // ray intersection
    return {true, origin + dv * t};
  }
  // line interesection but no ray intersection
  return {false, Vector3(0, 0, 0)};
}

Vector3 Triangle::get_normal(const Vector3& point) const {
    Vector3 perpendicular = (vertex1 - vertex0).cross_product(vertex2 - vertex0);
    perpendicular.normalize();
    return perpendicular;
}

}  // namespace Tracer