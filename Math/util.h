#pragma once
#include <math.h>
namespace math {
    inline float degreesToRadians(float degrees) {
      return degrees * (float)M_PI / 180;
    }
    inline float quadDiscr(float a, float b, float c) {
      return b * b - 4 * a * c;
    }
}
