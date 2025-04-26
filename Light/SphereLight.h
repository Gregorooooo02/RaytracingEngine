#pragma once

#include "Light.h"

namespace licht {
    class SphereLight : public Light {
    public:
        math::vec3 position;
        float radius;

        float constAttenuation;
        float linearAttenuation;
        float quadraticAttenuation;

        int samples;

        SphereLight(cam::LightIntensity intensity, math::vec3 position,
            float radius, float constAttenuation = 1.0f,
            float linearAttenuation = 0.0f,
            float quadraticAttenuation = 0.0f,
            int samples = 1
        );
        SphereLight();

        cam::LightIntensity getAmbient(math::primitive* object) override;
        cam::LightIntensity getDiffuse(math::vec3 point, math::primitive* object) override;
        cam::LightIntensity getSpecular(math::vec3 point, math::primitive* object, cam::Camera* camera) override;

        math::ray getShadowRay(math::vec3 origin) override;
        math::vec3 getPosition() override;
        void sampleLight(math::vec3 &point, math::vec3 &wi, cam::LightIntensity &Le, float &pdfLight, math::vec3 &samplePos) override;
    };
} // namespace licht