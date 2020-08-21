#ifndef SHAPE_H_
#define SHAPE_H_


#include "vector3.h"
#include <vector>
namespace Tracer{
    //base class for Triangle and Sphere
    class Shape{
      public:
        virtual ~Shape() = default;
        virtual std::pair<bool, Vector3> intersects(const Vector3& origin, const Vector3& dv) const = 0;
        virtual Vector3 get_normal(const Vector3& point) const = 0;
    };


}
#endif
