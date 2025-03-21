#pragma once

namespace math {
  class vec3 {
    public:
      float x, y, z;

      vec3();
      vec3(float x, float y, float z);
      vec3(vec3 &vec);
      ~vec3();

      vec3& add(vec3 &vec);
      vec3& substract(vec3 &vec);
      vec3& multiply(float multiplier);
      vec3& divide(float divider);
      float len();

      vec3& normalize();
      float dotProduct(vec3 &vec);
      vec3 crossProduct(vec3 &vec);

      vec3 rotate(float, vec3&);
  };
} // namespace math
