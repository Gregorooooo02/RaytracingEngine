#pragma once

#include "Material.h"
#include "ray.h"

namespace math {
  class primitive {
    public:
      Material material;
      virtual vec3* hit(ray &ray) = 0;
      virtual vec3 getNormal(vec3 point) = 0;
  };
}
