#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "shape.h"
#include "vector3.h"
namespace Tracer {
class Triangle : public Shape {
 public:
  Triangle(Vector3 v1, Vector3 v2, Vector3 v3)
      : vertex0(v1), vertex1(v2), vertex2(v3){}
  // overrides
  std::pair<bool, Vector3> intersects(const Vector3& origin,
                                      const Vector3& dv) const override;
  Vector3 get_normal(const Vector3& point) const override;

  Vector3 vertex0;
  Vector3 vertex1;
  Vector3 vertex2;
};
}  // namespace Tracer
#endif