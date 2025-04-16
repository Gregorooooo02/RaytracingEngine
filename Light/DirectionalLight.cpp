#include "DirectionalLight.h"
#include "ray.h"

#include <algorithm>
#include <cmath>

using namespace licht;

DirectionalLight::DirectionalLight(cam::LightIntensity intensity,
                                   math::vec3 direction)
    : Light(intensity), direction(-direction) {}

DirectionalLight::DirectionalLight()
    : Light(cam::LightIntensity(1, 1, 1)), direction(math::vec3(0, -1, -1)) {
} // Default direction is -YZ

cam::LightIntensity DirectionalLight::getAmbient(math::primitive *object) {
  return this->intensity * object->material.ambient;
}

cam::LightIntensity DirectionalLight::getDiffuse(math::vec3 point,
                                                 math::primitive *object) {
  math::vec3 normal = object->getNormal(point);
  math::vec3 lightDir = this->direction.normalize();

  float diffuseFactor = std::max(0.0f, normal.dotProduct(lightDir));

  return this->intensity * object->material.diffuse * diffuseFactor;
}

cam::LightIntensity DirectionalLight::getSpecular(math::vec3 point, math::primitive* object, cam::Camera* camera) {
    math::vec3 normal = object->getNormal(point);
    math::vec3 lightDir = this->direction.normalize();
    math::vec3 viewDir = (camera->position - point).normalize(); // Assuming camera->position is the camera position

    math::vec3 R = (normal * (2.0f * normal.dotProduct(lightDir)) - lightDir).normalize();
    float specAngle = std::max(0.0f, R.dotProduct(viewDir));
    float specularFactor = std::pow(specAngle, object->material.shininess);

    return this->intensity * object->material.specular * specularFactor;
}

math::ray DirectionalLight::getShadowRay(math::vec3 origin) {
  math::ray ray;
  ray.o = origin;
  ray.d = this->direction;
  return ray;
}

math::vec3 DirectionalLight::getPosition() {
  return {0, 0, 0}; // Directional light has no specific position
}
