#include "PointLight.h"

#include <algorithm>
#include <cmath>

using namespace licht;

PointLight::PointLight(cam::LightIntensity intensity, math::vec3 position,
                       float constAttenuation, float linearAttenuation,
                       float quadraticAttenuation)
    : Light(intensity), position(position),
      constAttenuation(constAttenuation), linearAttenuation(linearAttenuation),
      quadraticAttenuation(quadraticAttenuation) {}

PointLight::PointLight() {
    intensity = cam::LightIntensity(1, 1, 1);
    position = math::vec3(0, 0, 0);
    constAttenuation = 1.0f;
    linearAttenuation = 0.0f;
    quadraticAttenuation = 0.0f;
}

cam::LightIntensity PointLight::getAmbient(math::primitive *object) {
    return this->intensity * object->material.ambient;
}

cam::LightIntensity PointLight::getDiffuse(math::vec3 point,
                                            math::primitive *object) {
    math::vec3 normal = object->getNormal(point);
    math::vec3 lightDir = (this->position - point).normalize();

    float diffuseFactor = std::max(0.0f, normal.dotProduct(lightDir));
    float distance = (this->position - point).len();
    float attenuation =
        1.0f / (this->constAttenuation +
                this->linearAttenuation * distance +
                this->quadraticAttenuation * distance * distance);

    return this->intensity * object->material.diffuse * diffuseFactor *
           attenuation;
}

cam::LightIntensity PointLight::getSpecular(math::vec3 point, math::primitive *object, cam::Camera *camera) {
    math::vec3 normal = object->getNormal(point);
    math::vec3 lightDir = (this->position - point).normalize();
    math::vec3 viewDir = (camera->position - point).normalize(); // Assuming camera->position is the camera position

    math::vec3 R = (normal * (2.0f * normal.dotProduct(lightDir)) - lightDir).normalize();
    float specAngle = std::max(0.0f, R.dotProduct(viewDir));
    float specularFactor = std::pow(specAngle, object->material.shininess);

    float distance = (this->position - point).len();
    float attenuation =
        1.0f / (this->constAttenuation +
                this->linearAttenuation * distance +
                this->quadraticAttenuation * distance * distance);

    return this->intensity * object->material.specular * specularFactor *
           attenuation;
}

math::ray PointLight::getShadowRay(math::vec3 origin) {
    math::ray ray;
    ray.o = origin;
    ray.d = (this->position - origin).normalize();
    return ray;
}