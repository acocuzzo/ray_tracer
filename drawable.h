#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <memory>

#include "material.h"
#include "shape.h"

namespace Tracer {
class Drawable {
 public:
    Drawable();
    Drawable(std::unique_ptr<Shape> shape_ptr, Material m) : shape(std::move(shape_ptr)), material(m) {}

inline Shape* get_shape() const { return shape.get();}
inline Material get_material() const {return material;}
inline float get_diffusion_reflection() const {return material.diffuse_reflection;}
inline float get_ambient_reflection() const {return material.ambient_reflection;}
inline float get_specular_reflection() const {return material.specular_reflection;}
inline Color_UINT8 get_color() const{return material.color;}
inline Color_F get_color_f() const{return Color_F(material.color);}
inline Vector3 get_normal(const Vector3& point) const {return shape->get_normal(point);}
inline std::pair<bool, Vector3> intersects(const Vector3& origin, const Vector3& dv) const {return shape->intersects(origin, dv);}

private:
  std::unique_ptr<Shape> shape;
  Material material;
};
}  // namespace Tracer
#endif