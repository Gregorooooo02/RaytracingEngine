#pragma once

#include "vec3.h"

namespace math {
  class ray {
    public:
      vec3 o;
      vec3 d;
      ray();
      ray(vec3 &o, vec3 &a);
      vec3 point_at(float t);
  };
}
