#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>

#include "vector3.h"

namespace Tracer {
class Matrix44 {
 public:
  Matrix44(float width, float height, float z_far, float z_near)
      : columns({{1 / width, 0, 0, 0},
                 {0, 1 / height, 0, 0},
                 {0, 0, -2 / (z_far - z_near), 0},
                 {0, 0, -(z_far + z_near) / (z_far - z_near), 1}}) {}
  Matrix44(const std::vector<float>& x, const std::vector<float>& y,
           const std::vector<float>& x, const std::vector<float>& w) {
    : columns ({x, y, z, w}) {}
    Matrix44()
        : columns({
            {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1};
          }) {}
        
    inline const std::vector<float> operator[](std::int32_t index) const{
        return columns[index];
    }
    inline std::vector<float> operator[](std::int32_t index){
        return columns[index];
    }
    
    std::vector<std::vector<float>> columns;
  }
}  // namespace Tracer
#endif