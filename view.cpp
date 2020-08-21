#include "view.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "drawable.h"
#include "equality_checks.h"
#include "qdbmp.h"
#include "shape.h"
#include "sphere.h"
#include "vector3.h"

namespace Tracer {
namespace {

Color_UINT8 get_ambient_intensity(const Drawable& drawable,
                                  float view_ambience) {
  return drawable.get_color() * drawable.get_ambient_reflection() *
         view_ambience;
}

float get_diffusion_factor(const Drawable& drawable, const Light& light,
                           const Vector3& point, const Vector3& normal,
                           const Vector3& light_direction) {
  return drawable.get_diffusion_reflection() * light_direction.dot(normal) *
         light.get_diffuse();
}
float get_specular_factor(const Drawable& drawable, const Light& light,
                          const Vector3& point, const Vector3& normal,
                          const Vector3& viewer_direction) {
  return drawable.get_specular_reflection() *
         pow((light.get_reflection(point, normal).dot(viewer_direction)),
             drawable.get_material().shininess) *
         light.get_specular();
}
Color_UINT8 shade_point(const Drawable& drawable, const Vector3& point,
                        const std::vector<Light>& lights,
                        const Vector3& viewer_direction, float view_ambience) {
  Color_UINT8 final_color = get_ambient_intensity(drawable, view_ambience);
  for (const auto& light : lights) {
    Vector3 light_direction = light.get_direction(point);
    float light_distance =
        Vector3::get_distance_squared(light.get_position(), point);
    Vector3 normal = drawable.get_normal(point);
    float diffuse_factor =
        get_diffusion_factor(drawable, light, point, normal, light_direction);
    if (diffuse_factor / light_distance > 0) {
      final_color += drawable.get_color() * (diffuse_factor / light_distance);
      float specular_factor =
          get_specular_factor(drawable, light, point, normal, viewer_direction);
      if (specular_factor / light_distance > 0) {
        final_color += light.get_color() * (specular_factor / light_distance);
      }
    }
  }
  return final_color;
}

}  // namespace

std::vector<std::vector<Color_UINT8>> View::get_color_matrix() {
  std::vector<std::vector<Color_UINT8>> color_vector(
      pixel_height,
      std::vector<Color_UINT8>(pixel_width, Color_UINT8(0, 0, 0)));
  for (std::int32_t row = 0; row < pixel_height; ++row) {
    for (std::int32_t col = 0; col < pixel_width; ++col) {
      color_vector[row][col] = get_color_per_pixel(row, col);
    }
  }

  return color_vector;
}

Color_UINT8 View::get_color_per_pixel(std::int32_t row, std::int32_t col) {
  float view_height = 1;
  float view_width = 1;
  float x =
      (static_cast<float>(-pixel_width) / 2. + col) / pixel_width * view_width;
  float y = (static_cast<float>(pixel_height) / 2. - row) / pixel_height *
            view_height;
  Vector3 screen_pos = Vector3(x, y, 0);
  Vector3 eye_to_pixel =
      Vector3::get_direction_vector(focal_position, screen_pos);
  Vector3 closest_intersection = Vector3(0, 0, max_depth);
  Drawable* closest_drawable = nullptr;
  std::int32_t shape_count = 0;
  for (auto& s : drawables) {
    auto intersection = s.get_shape()->intersects(screen_pos, eye_to_pixel);
    if (intersection.first &&
        intersection.second.closer_to_screen_than(closest_intersection)) {
      closest_intersection = intersection.second;
      closest_drawable = &s;
    }
    shape_count += 1;
  }
  if (closest_intersection.z < max_depth) {
    return shade_point(*closest_drawable, closest_intersection, lights,
                       eye_to_pixel, ambience);
  }
  return shade_background_point();
}
}  // namespace Tracer

int main(int argc, char** argv) {
  uint width = 600;
  uint height = 600;
  float radius = .4;
  std::int32_t focal_length = 10;
  std::int16_t max_depth = 100;
  auto green = Tracer::Color_UINT8(0, 255, 0);
  auto light_blue = Tracer::Color_UINT8(0, 191, 255);
  Tracer::View this_view(width, height, focal_length, max_depth, light_blue);
  std::int32_t sphere_distance = 1;
  for (const auto& x : {0.}) {
    for (const auto& y : {0.}) {
      Tracer::Sphere* sphere =
          new Tracer::Sphere(radius, Tracer::Vector3(x, y, sphere_distance));
      std::unique_ptr<Tracer::Shape> s_ptr(std::move(sphere));
      Tracer::Drawable drawable(std::move(s_ptr), Tracer::Material(green));
      this_view.insert_drawable(drawable);
    }
  }
  float spec = .5;
  float diff = .5;
  this_view.add_light(
      Tracer::Light(Tracer::Vector3(-.5, .5, 0), spec, diff, 3));
  auto c_vector = this_view.get_color_matrix();
  BMP* bmp = BMP_Create(width, height, 24);
  for (unsigned long x = 0; x < width; ++x) {
    for (unsigned long y = 0; y < height; ++y) {
      BMP_SetPixelRGB(bmp, x, y, c_vector.at(y).at(x).red,
                      c_vector.at(y).at(x).green, c_vector.at(y).at(x).blue);
    }
  }
  BMP_WriteFile(bmp, "/home/anna/code/ray_tracer/bmp.bmp");
  BMP_Free(bmp);
}