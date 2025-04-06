#include "AreaLight.h"

#include <algorithm>
#include <cstdlib>

using namespace licht;

AreaLight::AreaLight(cam::LightIntensity intensity, math::vec3 position,
                     math::vec3 u, math::vec3 v, int samplesU, int samplesV)
                     : Light(intensity), position(position), u(u), v(v),
                     samplesU(samplesU), samplesV(samplesV) {}

AreaLight::AreaLight() {
    intensity = cam::LightIntensity(1, 1, 1);
    position = math::vec3(0, 0, 0);
    u = math::vec3(1, 0, 0);
    v = math::vec3(0, 1, 0);
    samplesU = 2;
    samplesV = 2;
}

cam::LightIntensity AreaLight::getAmbient(math::primitive *object) {
    return this->intensity * object->material.ambient;
}

cam::LightIntensity AreaLight::getDiffuse(math::vec3 point, math::primitive *object) {
    cam::LightIntensity totalDiffuse(0, 0, 0);
    int totalSamples = samplesU * samplesV;

    for (int i = 0; i < samplesU; i++) {
        for (int j = 0; j < samplesV; j++) {
            float ru = (i + static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) / samplesU;
            float rv = (j + static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) / samplesV;

            math::vec3 samplePos = position + ((ru - 0.5f) * 2.0f) * u + ((rv - 0.5f) * 2.0f) * v;
            math::vec3 L = (samplePos - point).normalize();

            float diffuseFactor = std::max(0.0f, object->getNormal(point).dotProduct(L));

            totalDiffuse = (totalDiffuse + (this->intensity * object->material.diffuse * diffuseFactor));
        }
    }

    return totalDiffuse / static_cast<float>(totalSamples);
}

cam::LightIntensity AreaLight::getSpecular(math::vec3 point, math::primitive *object, cam::Camera *camera) {
    cam::LightIntensity totalSpecular(0, 0, 0);
    int totalSamples = samplesU * samplesV;
    math::vec3 viewDir = (camera->position - point).normalize();

    for (int i = 0; i < samplesU; i++) {
        for (int j = 0; j < samplesV; j++) {
            float ru = (i + static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) / samplesU;
            float rv = (j + static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) / samplesV;

            math::vec3 samplePos = position + ((ru - 0.5f) * 2.0f) * u + ((rv - 0.5f) * 2.0f) * v;
            math::vec3 L = (samplePos - point).normalize();

            math::vec3 R = (object->getNormal(point) * (2.0f * object->getNormal(point).dotProduct(L)) - L).normalize();
            float specAngle = std::max(0.0f, R.dotProduct(viewDir));
            float specularFactor = std::pow(specAngle, object->material.shininess);

            totalSpecular = (totalSpecular + (this->intensity * object->material.specular * specularFactor));
        }
    }

    return totalSpecular / static_cast<float>(totalSamples);
}

math::ray AreaLight::getShadowRay(math::vec3 origin) {
    math::ray ray;
    ray.o = origin;
    ray.d = (this->position - origin).normalize();
    return ray;
}