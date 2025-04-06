#pragma once

#include "Light.h"

namespace licht {
    class AreaLight : public Light {
    public:
        math::vec3 position;
        // The two vectors defining the plane of the area light
        math::vec3 u;
        math::vec3 v;
        // The number of samples to take in the area light
        int samplesU;
        int samplesV;

        AreaLight(cam::LightIntensity intensity, math::vec3 position,
            math::vec3 u, math::vec3 v, int samplesU = 1, int samplesV = 1);
        AreaLight();

        cam::LightIntensity getAmbient(math::primitive* object) override;
        cam::LightIntensity getDiffuse(math::vec3 point, math::primitive* object) override;
        cam::LightIntensity getSpecular(math::vec3 point, math::primitive* object, cam::Camera* camera) override;
        math::ray getShadowRay(math::vec3 origin) override;
    };
} // namespace licht
