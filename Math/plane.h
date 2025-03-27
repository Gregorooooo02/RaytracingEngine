#pragma once

#include "vec3.h"
#include "ray.h"

namespace math {
    class plane {
        public:
            plane();
            plane(float, float, float, float);
            plane(const vec3&, float);
            plane(vec3&, vec3&);
            plane(vec3&, vec3&, vec3&);
            plane(const plane&);
            ~plane();

            bool hit(ray&);

        private:
            float a, b, c, d;
            vec3 normal;
            vec3 point;

    };
} // namespace math