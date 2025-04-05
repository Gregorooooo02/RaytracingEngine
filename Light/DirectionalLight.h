#pragma once

#include "Light.h"

namespace licht {
    class DirectionalLight : public Light {
    public:
        math::vec3 direction;

        DirectionalLight(cam::LightIntensity intensity, math::vec3 direction);
        DirectionalLight();

        cam::LightIntensity getAmbient(math::primitive* object) override;
        cam::LightIntensity getDiffuse(math::vec3 point, math::primitive* object) override;
        cam::LightIntensity getSpecular(math::vec3 point, math::primitive* object, cam::Camera* camera) override;
        math::ray getShadowRay(math::vec3 origin) override;

        // int isInShadow(bool isHit, math::primitive* object);
    };
} // namespace licht
