#pragma once

#include "ray.h"
namespace math {
  class primitive {
    public:
      virtual bool hit(ray &ray, float tMin, float tMax) = 0;
  };
}
