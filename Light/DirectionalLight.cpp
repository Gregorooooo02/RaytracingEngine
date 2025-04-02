#include "DirectionalLight.h"
#include "ray.h"

#include <algorithm>
#include <cmath>

using namespace licht;

DirectionalLight::DirectionalLight(cam::LightIntensity intensity, math::vec3 direction)
    : Light(intensity), direction(direction) {}

DirectionalLight::DirectionalLight()
    : Light(cam::LightIntensity(1, 1, 1)), direction(math::vec3(0, -1, -1)) {} // Default direction is -YZ

cam::LightIntensity DirectionalLight::getAmbient(math::primitive* object) {
    return this->intensity * object->material.ambient;
}

cam::LightIntensity DirectionalLight::getDiffuse(math::vec3 point, math::primitive* object) {
    math::vec3 normal = object->getNormal(point);
    math::vec3 lightDir = this->direction.normalize();

    float dotProduct = std::max(0.0f, normal.dotProduct(lightDir));

    return this->intensity * object->material.diffuse * dotProduct;
}

cam::LightIntensity DirectionalLight::getSpecular(math::vec3 point, math::primitive* object) {
    math::vec3 normal = object->getNormal(point);
    math::vec3 lightDir = this->direction.normalize();
    math::vec3 specular(
        object->material.specular.getR(),
        object->material.specular.getG(),
        object->material.specular.getB()
    );

    math::vec3 viewDir = (point - specular).normalize(); // Assuming specular is the camera position

    math::vec3 reflectDir = lightDir.reflect(normal);
    float dotProduct = std::max(0.0f, reflectDir.dotProduct(viewDir));

    return this->intensity * object->material.specular * pow(dotProduct, object->material.shininess);
}
math::ray DirectionalLight::getShadowRay(math::vec3 origin) {
  math::ray ray;
  ray.o = origin;
  ray.d = -this->direction;
  return ray;
}
