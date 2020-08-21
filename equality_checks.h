#ifndef EQUALITY_CHECKS_H_
#define EQUALITY_CHECKS_H_

#include <algorithm>
#include <limits>
#include <cstdint>
namespace Tracer{

bool nearly_equal(float a, float b, float diff){
    return std::abs(a - b) < diff;
}
bool nearly_equal_epsilon(float a, float b, float epsilon) {
  float abs_a = std::abs(a);
  float abs_b = std::abs(b);
  float diff = std::abs(a - b);
  if (a == b) {
    return true;
  }
  if (a == 0 || b == 0 || (abs_a + abs_b < std::numeric_limits<float>::min())) {
    return diff < (epsilon * std::numeric_limits<float>::min());
  }
  return diff / std::min((abs_a + abs_b),
                                 std::numeric_limits<float>::max()) <
         epsilon;
}
bool nearly_equal_ulps(float a, float b, std::int32_t max_ulps_diff) {
  bool a_is_neg = a < 0;
  bool b_is_neg = b < 0;
  if (a_is_neg != b_is_neg) {
      return a == b;
  }
  std::int32_t a_int = static_cast<std::int32_t>(a);
  std::int32_t b_int = static_cast<std::int32_t>(b);
  std::int32_t ulps_diff = abs(a_int - b_int);
  return ulps_diff <= max_ulps_diff;
}
}
#endif