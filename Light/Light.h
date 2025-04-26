#pragma once

#include "LightIntensity.h"
#include "Camera.h"
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
        virtual cam::LightIntensity getSpecular(math::vec3 point, math::primitive* object, cam::Camera* camera) = 0;
        virtual math::ray getShadowRay(math::vec3 origin) = 0;
        virtual math::vec3 getPosition() = 0;
        virtual void sampleLight(math::vec3 &point, math::vec3 &wi,
                                 cam::LightIntensity &Le, float &pdfLight, math::vec3 &samplePos) = 0;
        // virtual int isInShadow(bool isHit, math::primitive* object) = 0;
    };
} // namespace licht
