#include "Scene.h"
#include "AreaLight.h"
#include "Light.h"
#include "LightIntensity.h"
#include "Orthographic.h"
#include "Perspective.h"
#include "primitive.h"
#include "vec3.h"

#include <cmath>
#include <iostream>
#include <ostream>
#include <vector>

using namespace cam;

Scene::Scene() {
  this->camera = new Perspective();
  this->lights = std::vector<licht::Light *>();
  this->objects = std::vector<math::primitive *>();

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      this->colors[i][j] = new LightIntensity;
    }
  }
}

Scene::Scene(Camera *camera, std::vector<licht::Light *> lights,
             std::vector<math::primitive *> objects,
             LightIntensity *colors[6][6]) {
  this->camera = camera;
  this->lights = lights;
  this->objects = objects;

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      this->colors[i][j] = colors[i][j];
    }
  }
}

Scene::Scene(Camera *camera, std::vector<licht::Light *> lights,
             std::vector<math::primitive *> objects, LightIntensity bg) {
  this->camera = camera;
  this->lights = lights;
  this->objects = objects;

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      this->colors[i][j] = &bg;
    }
  }
}

float shadowFactorOther(math::vec3 *intersection,
                        std::vector<math::primitive *> objects, int objectIndex,
                        licht::Light *light) {
  math::ray shadowRay = light->getShadowRay(*intersection);
  math::vec3 *hitShadow = nullptr;
  for (int o2 = 0; o2 < objects.size(); o2++) {
    if (o2 == objectIndex)
      continue;
    hitShadow = objects[o2]->hit(shadowRay);
    if (hitShadow != nullptr) {
      delete hitShadow;
      return 0.0f;
      break;
    }
    delete hitShadow;
  }

  return 1.0f;
}

float shadowFactorAreaLight(licht::AreaLight *areaLight,
                            math::vec3 *intersection,
                            std::vector<math::primitive *> objects,
                            int objectIndex) {
  int totalSamples = areaLight->samplesU * areaLight->samplesV;
  int unblocked = 0;
  const float eps = 1e-4f;

  math::vec3 normal = objects[objectIndex]->getNormal(*intersection);
  math::vec3 shadowOrigin = *intersection + normal * eps;

  for (int s = 0; s < totalSamples; s++) {
    math::ray shadowRay = areaLight->getShadowRay(shadowOrigin);
    bool blocked = false;
    for (int o2 = 0; o2 < objects.size(); o2++) {
      if (o2 == objectIndex)
        continue;
      math::vec3 *hitShadow = objects[o2]->hit(shadowRay);
      if (hitShadow != nullptr) {
        delete hitShadow;
        blocked = true;
        break;
      }
      delete hitShadow;
    }
    if (!blocked)
      unblocked++;
  }
  return static_cast<float>(unblocked) / totalSamples;
}

math::ray getReflectionRay(math::vec3 hitDirection, math::vec3 hitPoint,
                           math::primitive *object) {
  math::ray result;
  result.o = hitPoint;

  math::vec3 normal = object->getNormal(hitPoint);
  math::vec3 r = hitDirection - (2 * normal * normal.dotProduct(hitDirection));

  result.d = r;

  return result;
}

Image Scene::renderScene(int width, int height) {
  float width_chunk_size = width / 6.0f;
  float height_chunk_size = height / 6.0f;
  Image img(width, height);

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int current_chunk_x = std::floor(x / width_chunk_size);
      int current_chunk_y = std::floor(y / height_chunk_size);
      LightIntensity pixel_color;

      for (int samples = 0; samples < camera->samplesCount; samples++) {
        bool hit = false;
        math::ray ray = camera->generateRay(x, y, width, height);

        for (int o = 0; o < this->objects.size(); o++) {
          math::vec3 *intersection = this->objects[o]->hit(ray);

          if (intersection != nullptr) {
            for (int l = 0; l < this->lights.size(); l++) {
              float shadowFactor;

              if (licht::AreaLight *areaLight =
                      dynamic_cast<licht::AreaLight *>(this->lights[l])) {
                shadowFactor = shadowFactorAreaLight(areaLight, intersection,
                                                     this->objects, o);
              } else {
                shadowFactor = shadowFactorOther(intersection, this->objects, o,
                                                 this->lights[l]);
              }

              pixel_color =
                  pixel_color + this->lights[l]->getAmbient(this->objects[o]);
              if (shadowFactor > 0.0f) {
                pixel_color = pixel_color +
                              (this->lights[l]->getDiffuse(*intersection,
                                                           this->objects[o]) *
                               shadowFactor);
                pixel_color =
                    pixel_color +
                    (this->lights[l]->getSpecular(
                         *intersection, this->objects[o], this->camera) *
                     shadowFactor);
              }
            }
            hit = true;
            break;
          }
          delete intersection;
        }
        if (!hit) {
          pixel_color =
              pixel_color + *this->colors[current_chunk_x][current_chunk_y];
        }
      }
      pixel_color = pixel_color / camera->samplesCount;
      img.setPixel(x, y, pixel_color);
    }
  }

  Camera *cam = this->camera;
  if (dynamic_cast<Perspective *>(cam)) {
    img.save("perspective.ppm");
    std::cout << "Image saved as perspective.ppm" << std::endl;
  } else if (dynamic_cast<Orthographic *>(cam)) {
    img.save("orthographic.ppm");
    std::cout << "Image saved as orthographic.ppm" << std::endl;
  } else {
    std::cout << "Unknown camera type." << std::endl;
  }

  return img;
}
