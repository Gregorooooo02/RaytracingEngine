#pragma once
#include <cmath>
#include <math.h>

namespace math {
    inline float degreesToRadians(float degrees) {
      return degrees * (float)M_PI / 180;
    }

    inline float quadDiscr(float a, float b, float c) {
      return b * b - 4 * a * c;
    }

    inline float root(float b, float discriminant, float a) {
      return ((b * - 1) + std::sqrt(discriminant)) / a;
    }
}
