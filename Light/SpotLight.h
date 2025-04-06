#pragma once

#include "Light.h"

namespace licht {
    class SpotLight : public Light {
    public:
        math::vec3 position;
        math::vec3 direction;

        float constAttenuation;
        float linearAttenuation;
        float quadraticAttenuation;
        float cutOffAngle;
        float dropOffAngle;

        SpotLight(cam::LightIntensity intensity, math::vec3 position,
            math::vec3 direction, float constAttenuation = 1.0f,
            float linearAttenuation = 0.0f, float quadraticAttenuation = 0.0f,
            float cutOffAngle = 30.0f, float dropOffAngle = 45.0f
        );
        SpotLight();

        cam::LightIntensity getAmbient(math::primitive* object) override;
        cam::LightIntensity getDiffuse(math::vec3 point, math::primitive* object) override;
        cam::LightIntensity getSpecular(math::vec3 point, math::primitive* object, cam::Camera* camera) override;
        math::ray getShadowRay(math::vec3 origin) override;
    };
} // namespace licht
