#pragma once

namespace math {
  class vec3 {
    public:
      float x, y, z;

      vec3();

      vec3(float x, float y, float z);
      vec3(const vec3 &vec);
      vec3& operator=(const vec3 &vec);
      ~vec3();

      vec3 add(const vec3 &vec) const;
      vec3 substract(const vec3 &vec) const;
      vec3 multiply(float multiplier) const;
      vec3 divide(float divider) const;
      float len();

      vec3 normalize();
      float dotProduct(vec3 &vec);
      vec3 crossProduct(vec3 &vec);

      vec3 rotate(float, vec3&);
  };


  vec3 operator+(const vec3 &v1, const vec3 &v2);
  vec3 operator-(const vec3 &v1, const vec3 &v2);
  vec3 operator-(const vec3 &v);
  vec3 operator*(const vec3 &v, float scalar);
  vec3 operator*(float scalar, const vec3 &v);
  vec3 operator/(const vec3 &v, float scalar);

} // namespace math
