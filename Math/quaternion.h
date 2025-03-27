#pragma once

#include "vec3.h"

namespace math {
    class quaternion {
        public:
            float s;
            vec3 v;

            quaternion();
            quaternion(float s, vec3& v);
            ~quaternion();
            quaternion(const quaternion& q);
            quaternion& operator=(const quaternion& q);

            quaternion add(quaternion& q);
            quaternion substract(quaternion& q);
            quaternion multiply(quaternion& q);
            quaternion multiply(float scalar);

            float norm();
            void normalize();
            quaternion conjugate();
            quaternion inverse();

            void convertToUnitNorm();
    };

} // namespace math
