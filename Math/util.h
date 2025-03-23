#pragma once
#include <cmath>
#include <math.h>

namespace math {
    inline float degreesToRadians(float degrees) {
      return degrees * (float)M_PI / 180;
    }

    inline float quadDiscr(float a, float b, float c) {
      return b * b - a * c;
    }

    inline float root(float b, float discriminant, float a) {
      if (discriminant > 0) {
        return (-b + std::sqrt(discriminant)) / a;
      }
      else {
        return (-b - std::sqrt(-discriminant)) / a;
      }
    }
}
