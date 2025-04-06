#include "SpotLight.h"

#include <algorithm>
#include <cmath>

using namespace licht;

SpotLight::SpotLight(cam::LightIntensity intensity, math::vec3 position,
                    math::vec3 direction, float constAttenuation,
                    float linearAttenuation, float quadraticAttenuation,
                    float cutOffAngle, float dropOffAngle)
                    : Light(intensity), position(position), direction(direction),
                    constAttenuation(constAttenuation), linearAttenuation(linearAttenuation),
                    quadraticAttenuation(quadraticAttenuation), cutOffAngle(cutOffAngle),
                    dropOffAngle(dropOffAngle) {}

SpotLight::SpotLight() {
    intensity = cam::LightIntensity(1, 1, 1);
    position = math::vec3(0, 0, 0);
    direction = math::vec3(0, 0, -1);
    constAttenuation = 1.0f;
    linearAttenuation = 0.0f;
    quadraticAttenuation = 0.0f;
    cutOffAngle = 30.0f;
    dropOffAngle = 45.0f;
}

cam::LightIntensity SpotLight::getAmbient(math::primitive *object) {
    return this->intensity * object->material.ambient;
}

cam::LightIntensity SpotLight::getDiffuse(math::vec3 point, math::primitive *object) {
    math::vec3 lightDir = (this->position - point).normalize();
    float spotFactor = this->direction.normalize().dotProduct(lightDir);
    float cosCutOff = std::cos(cutOffAngle * M_PI / 180.0f);

    // Check if the point is within the cut-off angle (inside the light cone)
    if (spotFactor < cosCutOff) {
        return cam::LightIntensity(0, 0, 0); // Outside the cut-off angle
    }

    float distance = (this->position - point).len();
    float attenuation =
        1.0f / (this->constAttenuation +
                this->linearAttenuation * distance +
                this->quadraticAttenuation * distance * distance);

    float dropOffFactor = std::pow(spotFactor, dropOffAngle);
    math::vec3 normal = object->getNormal(point);
    float diffuseFactor = std::max(0.0f, normal.dotProduct(lightDir));

    return this->intensity * object->material.diffuse * diffuseFactor *
        attenuation * dropOffFactor;
}

cam::LightIntensity SpotLight::getSpecular(math::vec3 point, math::primitive *object, cam::Camera *camera) {
    math::vec3 lightDir = (this->position - point).normalize();
    float spotFactor = this->direction.normalize().dotProduct(lightDir);
    float cosCutOff = std::cos(cutOffAngle * M_PI / 180.0f);

    // Check if the point is within the cut-off angle (inside the light cone)
    if (spotFactor < cosCutOff) {
        return cam::LightIntensity(0, 0, 0); // Outside the cut-off angle
    }

    float distance = (this->position - point).len();
    float attenuation =
        1.0f / (this->constAttenuation +
                this->linearAttenuation * distance +
                this->quadraticAttenuation * distance * distance);

    float dropOffFactor = std::pow(spotFactor, dropOffAngle);

    math::vec3 normal = object->getNormal(point);
    math::vec3 viewDir = (camera->position - point).normalize(); // Assuming camera->position is the camera position
    math::vec3 R = (normal * (2.0f * normal.dotProduct(lightDir)) - lightDir).normalize();
    float specAngle = std::max(0.0f, R.dotProduct(viewDir));
    float specularFactor = std::pow(specAngle, object->material.shininess);

    return this->intensity * object->material.specular * specularFactor *
        attenuation * dropOffFactor;
}

math::ray SpotLight::getShadowRay(math::vec3 origin) {
    math::ray ray;
    ray.o = origin;
    ray.d = (this->position - origin).normalize();
    return ray;
}
