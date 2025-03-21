#pragma once

#include "ray.h"

namespace math {
  class primitive {
    public:
      bool hit(ray &ray);
  };
}
