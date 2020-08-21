#ifndef COLOR_H_
#define COLOR_H_
#include <stdio.h>

#include <cassert>
#include <string>

namespace Tracer {

struct Color_F;
struct Color_UINT8 {
  Color_UINT8(std::uint8_t r, std::uint8_t g, std::uint8_t b);
  Color_UINT8(const Color_F& color_float);

  std::int32_t generate_hex() const;
  void print_hex() const;
  Color_UINT8 operator*(float scalar) const;
  void operator*=(float scalar);
  Color_UINT8 multiply_with_scaling(float scalar) const;
  void multiply_with_scaling_in_place(float scalar);
  Color_UINT8 operator+(const Color_UINT8& rhs) const;
  void operator+=(const Color_UINT8& rhs);
  Color_UINT8 addition_with_scaling(const Color_UINT8& rhs) const;
  Color_UINT8 addition_with_scaling(const Color_F& rhs) const;
  void addition_with_scaling_in_place(const Color_UINT8& rhs);
  void addition_with_scaling_in_place(const Color_F& rhs);

  std::uint8_t red;
  std::uint8_t green;
  std::uint8_t blue;
};
struct Color_F {
  Color_F(float r, float g, float b);
  Color_F(const Color_UINT8& color_u);
  
  std::int32_t generate_hex() const;
  void print_hex() const;

  Color_F operator*(float scalar) const;
  void operator*=(float scalar);
  Color_F operator+(const Color_F& rhs) const;
  Color_F operator+(const Color_UINT8& rhs) const;
  void operator+=(const Color_F& rhs);
  void operator+=(const Color_UINT8& rhs);

  Color_UINT8 color_scale() const;
  
  float red;
  float green;
  float blue;
};

}  // namespace Tracer
#endif