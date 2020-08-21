#include "light.h"

namespace Tracer{
    Vector3 Light::get_direction(const Vector3& point) const {
        Vector3 direction = position - point;
        direction.normalize();
        return direction;
    }

    Vector3 Light::get_reflection(const Vector3& point, const Vector3& normal) const{
        Vector3 light_direction = get_direction(point); 
        return (normal * (2 * light_direction.dot(normal))) - light_direction;
    }
}