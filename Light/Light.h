#pragma once

#include "LightIntensity.h"
#include "primitive.h"

namespace licht {
    class Light {
    public:
        cam::LightIntensity intensity;

        Light(cam::LightIntensity intensity);
        Light();
        virtual ~Light() = default;

        virtual cam::LightIntensity getAmbient(math::primitive* object) = 0;
        virtual cam::LightIntensity getDiffuse(math::vec3 point, math::primitive* object) = 0;
        virtual cam::LightIntensity getSpecular(math::vec3 point, math::primitive* object) = 0;
        virtual math::ray getShadowRay(math::vec3 origin) = 0;

        // virtual int isInShadow(bool isHit, math::primitive* object) = 0;
    };
} // namespace licht
