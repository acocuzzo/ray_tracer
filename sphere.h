#ifndef SPHERE_H_
#define SPHERE_H_

#include "vector3.h"
#include "shape.h"

#include <array>
#include <assert.h>
namespace Tracer {
class Sphere : public Shape{
    public:
    Sphere(float r, Vector3 center)
        : radius(r), center_position(center)
    {
        assert (r > 0);
    };
    // override
    std::pair<bool, Vector3> intersects(const Vector3& screen_pos, const Vector3& dv) const override;
    Vector3 get_normal(const Vector3& point) const override;

    float radius;
    Vector3 center_position;
};
}
#endif