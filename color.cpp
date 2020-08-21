#include "color.h"

#include <cstdint>
namespace Tracer {

 Color_UINT8::Color_UINT8(std::uint8_t r, std::uint8_t g, std::uint8_t b)
      : red(r), green(g), blue(b) {}
  Color_UINT8::Color_UINT8(const Color_F& color_float) {
    Color_UINT8 scaled_color = color_float.color_scale();
    red = scaled_color.red;
    green = scaled_color.green;
    blue = scaled_color.blue;
  }

std::int32_t Color_UINT8::generate_hex() const {
  return static_cast<std::int32_t>(red) << 8 |
         static_cast<std::int32_t>(green) << 4 |
         static_cast<std::int32_t>(blue);
}
void Color_UINT8::print_hex() const {
  printf("[%04x]", (static_cast<std::int32_t>(red) << 8) |
                       (static_cast<std::int32_t>(green) << 4) |
                       (static_cast<std::int32_t>(blue)));
}

Color_UINT8 Color_UINT8::operator*(float scalar) const {
  std::uint8_t new_red =
      (static_cast<std::int16_t>(red) * scalar >= 255) ? 255 : red * scalar;
  std::uint8_t new_green =
      (static_cast<std::int16_t>(green) * scalar >= 255) ? 255 : green * scalar;
  std::uint8_t new_blue =
      (static_cast<std::int16_t>(blue) * scalar >= 255) ? 255 : blue * scalar;
  return Color_UINT8(new_red, new_green, new_blue);
}

void Color_UINT8::operator*=(float scalar) {
  std::uint8_t new_red =
      (static_cast<std::int16_t>(red) * scalar >= 255) ? 255 : red * scalar;
  std::uint8_t new_green =
      (static_cast<std::int16_t>(green) * scalar >= 255) ? 255 : green * scalar;
  std::uint8_t new_blue =
      (static_cast<std::int16_t>(blue) * scalar >= 255) ? 255 : blue * scalar;
  red = new_red;
  green = new_green;
  blue = new_blue;
}
Color_UINT8 Color_UINT8::multiply_with_scaling(float scalar) const {
  float new_red = red * scalar;
  float new_green = green * scalar;
  float new_blue = blue * scalar;
  float total_color = new_red + new_green + new_blue;
  return Color_UINT8(static_cast<std::uint8_t>(new_red / total_color + .5),
                     static_cast<std::uint8_t>(new_green / total_color + .5),
                     static_cast<std::uint8_t>(new_blue / total_color + .5));
}
void Color_UINT8::multiply_with_scaling_in_place(float scalar) {
  float new_red = red * scalar;
  float new_green = green * scalar;
  float new_blue = blue * scalar;
  float total_color = new_red + new_green + new_blue;
  red = static_cast<std::uint8_t>(new_red / total_color + .5);
  green = static_cast<std::uint8_t>(new_green / total_color + .5);
  blue = static_cast<std::uint8_t>(new_blue / total_color + .5);
}
Color_UINT8 Color_UINT8::operator+(const Color_UINT8& rhs) const {
  std::uint8_t new_red =
      (static_cast<std::int16_t>(red) + static_cast<std::int16_t>(rhs.red) >=
       255)
          ? 255
          : red + rhs.red;
  std::uint8_t new_green = (static_cast<std::int16_t>(green) +
                                static_cast<std::int16_t>(rhs.green) >=
                            255)
                               ? 255
                               : green + rhs.green;
  std::uint8_t new_blue =
      (static_cast<std::int16_t>(blue) + static_cast<std::int16_t>(rhs.blue) >=
       255)
          ? 255
          : blue + rhs.blue;
  return Color_UINT8(new_red, new_green, new_blue);
}

void Color_UINT8::operator+=(const Color_UINT8& rhs) {
  red = (static_cast<std::int16_t>(red) + static_cast<std::int16_t>(rhs.red) >=
         255)
            ? 255
            : red + rhs.red;
  green = (static_cast<std::int16_t>(green) +
               static_cast<std::int16_t>(rhs.green) >=
           255)
              ? 255
              : green + rhs.green;
  blue =
      (static_cast<std::int16_t>(blue) + static_cast<std::int16_t>(rhs.blue) >=
       255)
          ? 255
          : blue + rhs.blue;
}

Color_UINT8 Color_UINT8::addition_with_scaling(const Color_UINT8& rhs) const {
  float new_red = red + rhs.red;
  float new_green = green + rhs.green;
  float new_blue = blue + rhs.blue;
  float total_color = new_red + new_green + new_blue;
  return Color_UINT8(static_cast<std::uint8_t>(new_red / total_color + .5),
                     static_cast<std::uint8_t>(new_green / total_color + .5),
                     static_cast<std::uint8_t>(new_blue / total_color + .5));
}
Color_UINT8 Color_UINT8::addition_with_scaling(const Color_F& rhs) const {
  float new_red = red + rhs.red;
  float new_green = green + rhs.green;
  float new_blue = blue + rhs.blue;
  float total_color = new_red + new_green + new_blue;
  return Color_UINT8(static_cast<std::uint8_t>(new_red / total_color + .5),
                     static_cast<std::uint8_t>(new_green / total_color + .5),
                     static_cast<std::uint8_t>(new_blue / total_color + .5));
}
void Color_UINT8::addition_with_scaling_in_place(const Color_UINT8& rhs) {
  float new_red = red + rhs.red;
  float new_green = green + rhs.green;
  float new_blue = blue + rhs.blue;
  float total_color = new_red + new_green + new_blue;
  red = static_cast<std::uint8_t>(new_red / total_color + .5);
  green = static_cast<std::uint8_t>(new_green / total_color + .5);
  blue = static_cast<std::uint8_t>(new_blue / total_color + .5);
}
void Color_UINT8::addition_with_scaling_in_place(const Color_F& rhs) {
  float new_red = red + rhs.red;
  float new_green = green + rhs.green;
  float new_blue = blue + rhs.blue;
  float total_color = new_red + new_green + new_blue;
  red = static_cast<std::uint8_t>(new_red / total_color + .5);
  green = static_cast<std::uint8_t>(new_green / total_color + .5);
  blue = static_cast<std::uint8_t>(new_blue / total_color + .5);
}

Color_F::Color_F(float r, float g, float b) : red(r), green(g), blue(b) {}
Color_F::Color_F(const Color_UINT8& color_u)
    : red(static_cast<float>(color_u.red)),
      green(static_cast<float>(color_u.green)),
      blue(static_cast<float>(color_u.blue)) {}
std::int32_t Color_F::generate_hex() const {
  return static_cast<std::int32_t>(red) << 8 |
           static_cast<std::int32_t>(green) << 4 |
           static_cast<std::int32_t>(blue);
}

void Color_F::print_hex() const {
   printf("[%04x]", (static_cast<std::int32_t>(red) << 8) |
                         (static_cast<std::int32_t>(green) << 4) |
                         (static_cast<std::int32_t>(blue)));
  
}

 Color_F Color_F::operator*(float scalar) const {
    return Color_F(red * scalar, green * scalar, blue * scalar);
  }

  void Color_F::operator*=(float scalar) {
    red *= scalar;
    green *= scalar;
    blue *= scalar;
  }

  Color_F Color_F::operator+(const Color_F& rhs) const {
    return Color_F(red + rhs.red, green + rhs.green, blue + rhs.blue);
  }
  Color_F Color_F::operator+(const Color_UINT8& rhs) const {
    return Color_F(red + rhs.red, green + rhs.green, blue + rhs.blue);
  }
  void Color_F::operator+=(const Color_F& rhs) {
    red += rhs.red;
    green += rhs.green;
    blue += rhs.blue;
  }
  void Color_F::operator+=(const Color_UINT8& rhs) {
    red += rhs.red;
    green += rhs.green;
    blue += rhs.blue;
  }
  Color_UINT8 Color_F::color_scale() const {
    float total_color = red + green + blue;
    float new_red = red / total_color * 255 + .5;
    float new_green = green / total_color * 255 + .5;
    float new_blue = blue / total_color * 255 + .5;
    return Color_UINT8(static_cast<std::uint8_t>(new_red),
                       static_cast<std::uint8_t>(new_green),
                       static_cast<std::uint8_t>(new_blue));
  }

}  // namespace Tracer