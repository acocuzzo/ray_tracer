#ifndef VIEW_H_
#define VIEW_H_

#include <cstdint>
#include <vector>

#include "light.h"
#include "material.h"
#include "sphere.h"
#include "vector3.h"
#include "triangle.h"
#include "drawable.h"

namespace Tracer {
class View {
 public:
  View(std::int32_t w, std::int32_t h, std::int32_t FL, std::int32_t MD)
      : focal_position(Vector3(0, 0, -FL)),
        pixel_height(h),
        pixel_width(w),
        max_depth(MD),
        background(Material(Color_UINT8(0, 0, 0))),
        ambience(1)
        {}
  View(std::int32_t w, std::int32_t h, std::int32_t FL, std::int32_t MD,
       Color_UINT8 b)
      : focal_position(Vector3(0, 0, -FL)),
        pixel_height(h),
        pixel_width(w),
        max_depth(MD),
        background(Material(b)),
        ambience(2) {}

  std::vector<std::vector<Color_UINT8>> get_color_matrix();
  inline void set_ambience(float a){
      ambience = a;
  }
  inline float get_ambience(){
      return ambience;
  }
  inline void insert_drawable(Drawable& drawable) { drawables.push_back(std::move(drawable)); }
  inline void add_light(const Light& light) { lights.push_back(light); }

static Drawable background_shape(){
    +
}
 private:
  Color_UINT8 get_color_per_pixel(std::int32_t x, std::int32_t y);
  Vector3 focal_position;
  std::int32_t pixel_height;
  std::int32_t pixel_width;
  std::int32_t max_depth;  // location of background
  std::vector<Light> lights;
  std::vector<Drawable> drawables;
  Drawable background;
  float ambience;
};

}  // namespace Tracer
#endif