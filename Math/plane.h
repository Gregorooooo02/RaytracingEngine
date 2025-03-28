#pragma once
#include "LightIntensity.h"
#include "primitive.h"
#include "vec3.h"
#include "ray.h"

namespace math {
    class plane : public primitive {
        public:
            plane();
            plane(float, float, float, float, cam::LightIntensity);
            plane(const vec3&, float, cam::LightIntensity);
            plane(vec3&, vec3&, cam::LightIntensity);
            plane(vec3&, vec3&, vec3&, cam::LightIntensity);
            plane(const plane&);
            ~plane();
            bool hit(ray&);
        private:
            float a, b, c, d;
            vec3 normal;
            vec3 point;

    };
} // namespace math
