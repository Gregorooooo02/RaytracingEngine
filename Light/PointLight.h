#pragma once

#include "Light.h"

namespace licht {
    class PointLight : public Light {
    public:
        math::vec3 position;
        float constAttenuation;
        float linearAttenuation;
        float quadraticAttenuation;

        PointLight(cam::LightIntensity intensity, math::vec3 position,
            float constAttenuation = 1.0f,
            float linearAttenuation = 0.0f,
            float quadraticAttenuation = 0.0f
        );
        PointLight();

        cam::LightIntensity getAmbient(math::primitive* object) override;
        cam::LightIntensity getDiffuse(math::vec3 point, math::primitive* object) override;
        cam::LightIntensity getSpecular(math::vec3 point, math::primitive* object, cam::Camera* camera) override;
        math::ray getShadowRay(math::vec3 origin) override;
        math::vec3 getPosition() override;
    };
} // namespace licht
