#pragma once
#include "vec3.h"

namespace math {
  class ray {
    public:
      vec3 origin;
      vec3 destination;
      ray();
      ray(vec3 &origin, vec3 &destination);
      vec3 point_at(float t);
      ~ray();
  };
}
