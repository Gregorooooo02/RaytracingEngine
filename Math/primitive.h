#pragma once

#include "LightIntensity.h"
#include "ray.h"

namespace math {
  class primitive {
    public:
      cam::LightIntensity color;
      virtual bool hit(ray &ray) = 0;
  };
}
