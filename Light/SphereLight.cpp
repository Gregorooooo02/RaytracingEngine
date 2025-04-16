#include "SphereLight.h"

#include <algorithm>
#include <cmath>

using namespace licht;

SphereLight::SphereLight(cam::LightIntensity intensity,
                               math::vec3 position, float radius,
                               float constAttenuation, float linearAttenuation,
                               float quadraticAttenuation, int samples)
    : Light(intensity), position(position), radius(radius),
    constAttenuation(constAttenuation), linearAttenuation(linearAttenuation),
    quadraticAttenuation(quadraticAttenuation), samples(samples) {}

SphereLight::SphereLight() {
  intensity = cam::LightIntensity(1, 1, 1);
  position = math::vec3(0, 0, 0);
  radius = 1.0f;
  constAttenuation = 1.0f;
  linearAttenuation = 0.0f;
  quadraticAttenuation = 0.0f;
  samples = 1;
}

cam::LightIntensity SphereLight::getAmbient(math::primitive *object) {
  return this->intensity * object->material.ambient;
}

cam::LightIntensity SphereLight::getDiffuse(math::vec3 point,
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

cam::LightIntensity SphereLight::getSpecular(math::vec3 point,
                                                  math::primitive *object,
                                                  cam::Camera *camera) {
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

math::ray SphereLight::getShadowRay(math::vec3 origin) {
  float u = static_cast<float>(rand()) / RAND_MAX;
  float v = static_cast<float>(rand()) / RAND_MAX;
  float theta = 2.0f * M_PI * u;
  float phi = acos(1.0f - 2.0f * v);
  float sinPhi = sin(phi);

  math::vec3 randomDirection(
    sinPhi * cos(theta),
    sinPhi * sin(theta),
    cos(phi)
  );

  math::vec3 samplePos = this->position + randomDirection * this->radius;

  math::ray shadowRay;
  shadowRay.o = origin;
  shadowRay.d = (samplePos - origin).normalize();

  return shadowRay;
}

math::vec3 SphereLight::getPosition() {
  return this->position;
}


