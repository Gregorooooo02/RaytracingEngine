#pragma once

namespace math {
  class vec3 {
    public:
      float x, y, z;

      vec3();
      vec3(float x, float y, float z);
      vec3(vec3 &vec);
      ~vec3();

      void add(vec3 &vec);
      void substract(vec3 &vec);
      vec3 multiply(float multiplier);
      void divide(float divider);
      float len();

      void normalize();
      float dotProduct(vec3 &vec);
      vec3 crossProduct(vec3 &vec);

      vec3 rotate(float, vec3&);
  };
} // namespace math