#include "Scene.h"
#include "AreaLight.h"
#include "Light.h"
#include "LightIntensity.h"
#include "Perspective.h"
#include "primitive.h"
#include "vec3.h"
#include <SoftPointLight.h>
#include <atomic>
#include <cmath>
#include <iostream>
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
             LightIntensity *colors[6][6], int maxDepth) {
  this->camera = camera;
  this->lights = lights;
  this->objects = objects;

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      this->colors[i][j] = colors[i][j];
    }
  }
  this->maxDepth = maxDepth;
}

Scene::Scene(Camera *camera, std::vector<licht::Light *> lights,
             std::vector<math::primitive *> objects, LightIntensity bg,
             int maxDepth) {
  this->camera = camera;
  this->lights = lights;
  this->objects = objects;

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      this->colors[i][j] = &bg;
    }
  }
  this->maxDepth = maxDepth;
}

struct IntersectionInfo {
  bool hit;
  float t;
  math::vec3 point;
  math::vec3 normal;
  math::primitive *object;
};

IntersectionInfo
findClosestIntersection(math::ray &ray,
                        std::vector<math::primitive *> &objects) {
  IntersectionInfo info;
  info.hit = false;
  info.t = std::numeric_limits<float>::max();
  float eps = 1e-4f;

  for (int o = 0; o < objects.size(); o++) {
    math::vec3 *hitPoint = objects[o]->hit(ray);
    if (hitPoint) {
      float tCandidate = (*hitPoint - ray.o).len();
      if (tCandidate < info.t && tCandidate > eps) {
        info.hit = true;
        info.t = tCandidate;
        info.point = *hitPoint;
        info.normal = objects[o]->getNormal(*hitPoint);
        info.object = objects[o];
      }
      delete hitPoint;
    }
  }
  return info;
}

float shadowFactorOther(math::vec3 *intersection,
                        std::vector<math::primitive *> objects, int objectIndex,
                        licht::Light *light) {
  math::ray shadowRay = light->getShadowRay(*intersection);
  math::vec3 *hitShadow = nullptr;
  math::vec3 lightPosition = light->getPosition();
  for (int o2 = 0; o2 < objects.size(); o2++) {
    if (o2 == objectIndex)
      continue;
    hitShadow = objects[o2]->hit(shadowRay);
    if (hitShadow != nullptr) {
      float tShadow = (*hitShadow - shadowRay.o).len();
      float tLight = (lightPosition - shadowRay.o).len();
      delete hitShadow;

      if (tShadow < tLight - 1e-4f) {
        return 0.0f; // Shadowed
      }
    }
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
        float tShadow = (*hitShadow - shadowRay.o).len();
        float tLight = (areaLight->getPosition() - shadowRay.o).len();
        delete hitShadow;
        if (tShadow < tLight - eps) {
          blocked = true; // Shadowed
          break;
        }
        break;
      }
      delete hitShadow;
    }
    if (!blocked)
      unblocked++;
  }
  return static_cast<float>(unblocked) / totalSamples;
}

float shadowFactorSoftPoint(licht::SphereLight *pointLight,
                            math::vec3 *intersection,
                            std::vector<math::primitive *> objects,
                            int objectIndex) {
  int totalSamples = pointLight->samples;
  int unblocked = 0;
  const float eps = 1e-4f;

  for (int s = 0; s < totalSamples; s++) {
    math::ray shadowRay = pointLight->getShadowRay(*intersection);
    bool blocked = false;
    for (int o2 = 0; o2 < objects.size(); o2++) {
      if (o2 == objectIndex) {
        continue;
      }
      math::vec3 *hitShadow = objects[o2]->hit(shadowRay);
      if (hitShadow != nullptr) {
        // Check if the intersection point is in shadow
        float tShadow = (*hitShadow - shadowRay.o).len();
        float tLight = (pointLight->getPosition() - shadowRay.o).len();
        delete hitShadow;
        // If the shadow ray intersects an object before reaching the light
        if (tShadow < tLight - eps) {
          blocked = true; // Shadowed
          break;
        }
        break;
      }
      delete hitShadow;
    }
    if (!blocked) {
      unblocked++;
    }
  }
  return static_cast<float>(unblocked) / totalSamples;
}

LightIntensity localIllumination(IntersectionInfo &info,
                                 std::vector<licht::Light *> &lights,
                                 std::vector<math::primitive *> &objects,
                                 Camera *camera) {
  LightIntensity pixel_color;

  for (int l = 0; l < lights.size(); l++) {
    int index = -1;

    for (int o = 0; o < objects.size(); o++) {
      if (objects[o] == info.object) {
        index = o;
        break;
      }
    }

    float shadowFactor = 1.0f;
    if (licht::AreaLight* areaLight = dynamic_cast<licht::AreaLight*>(lights[l])) {
      shadowFactor = shadowFactorAreaLight(areaLight, &info.point, objects, index);
    }
    else if (licht::SphereLight* pointLight = dynamic_cast<licht::SphereLight*>(lights[l])) {
      shadowFactor = shadowFactorSoftPoint(pointLight, &info.point, objects, index);
    }
    else {
      shadowFactor = shadowFactorOther(&info.point, objects, index, lights[l]);
    }

    pixel_color = pixel_color + lights[l]->getAmbient(info.object);
    if (shadowFactor > 0.0f) {
      pixel_color =
          pixel_color +
          (lights[l]->getDiffuse(info.point, info.object) * shadowFactor);
      pixel_color = pixel_color +
                    (lights[l]->getSpecular(info.point, info.object, camera) *
                     shadowFactor);
    }
  }

  return pixel_color;
}

math::ray getReflectionRay(math::vec3 &hitDirection, IntersectionInfo &info) {
  math::ray result;
  result.o =
      info.point + info.normal * 1e-4f; // Offset to avoid self-intersection

  math::vec3 normal = info.object->getNormal(info.point);
  math::vec3 r =
      hitDirection - (2 * normal * (normal.dotProduct(hitDirection)));

  result.d = r;

  return result;
}

math::ray getRefractedRay(math::ray &incidentRay, IntersectionInfo &info,
                          float iorExternal, float iorInternal) {
  math::ray result;
  // Incident ray direction - the ray that hits the object
  math::vec3 incidentDir = incidentRay.d.normalize();
  // Normal at the intersection point
  math::vec3 normal = info.object->getNormal(info.point).normalize();

  // Calculate the cosine of the angle of incidence
  float cos = incidentDir.dotProduct(normal);
  // eta - the ratio of the indices of refraction
  float eta;

  // Check if the ray is entering or exiting the material
  // If the cosine is negative, it means the ray is entering the material
  // If the cosine is positive, it means the ray is exiting the material
  if (cos < 0) {
    cos = -cos;
    eta = iorExternal / iorInternal;
  } else {
    normal = -normal;
    eta = iorInternal / iorExternal;
  }

  // In Snell's Law, the refract equation goes:
  // cos²θ₂ = 1 - eta²*(1 - cos²θ₁), so k is the cos²θ₂
  // If cos²θ₂ < 0, the refraction doesn't occur
  float k = 1.0f - eta * eta * (1 - cos * cos);
  if (k < 0.0f) {
    // If k < 0, total internal reflection occurs
    math::vec3 reflectRayDir =
        incidentDir - 2.0f * (normal * incidentDir.dotProduct(normal));
    reflectRayDir = reflectRayDir.normalize();

    result.o = info.point + normal * 1e-4f; // Offset to avoid self-intersection
    result.d = reflectRayDir;

    return result;
  } else {
    // Else, calculate the refracted ray
    // t = η * i + (η * cosθ₁ - sqrt(1 - η² * (1 - cosθ₁²))) * n
    // t = η * i + (η * cosθ₁ - sqrt(k)) * n
    math::vec3 refractRayDir =
        (incidentDir * eta) + (normal * (eta * cos - sqrt(k)));
    refractRayDir = refractRayDir.normalize();

    result.o = info.point - normal * 1e-4f; // Offset to avoid self-intersection
    result.d = refractRayDir;

    return result;
  }
}

LightIntensity shade(math::ray &ray, std::vector<licht::Light *> lights,
                     std::vector<math::primitive *> objects, Camera *camera,
                     LightIntensity bg, int depth, int maxDepth) {
  IntersectionInfo info = findClosestIntersection(ray, objects);
  LightIntensity pixel_color = localIllumination(info, lights, objects, camera);

  if (depth > maxDepth)
    return pixel_color;

  if (!info.hit)
    return bg;
  float reflectionFactor = info.object->material.reflection;
  float refractionFactor = info.object->material.refraction;

  if (refractionFactor > 0.0f) {
    math::ray refractionRay =
        getRefractedRay(ray, info, 1.0f, info.object->material.ior);
    LightIntensity refractionColor =
        shade(refractionRay, lights, objects, camera, bg, depth + 1, maxDepth);
    pixel_color = pixel_color * (1 - refractionFactor) +
                  refractionColor * refractionFactor;
  }

  if (reflectionFactor > 0.0f) {
    math::ray reflectionRay = getReflectionRay(ray.d, info);
    LightIntensity reflectionColor =
        shade(reflectionRay, lights, objects, camera, bg, depth + 1, maxDepth);
    pixel_color = pixel_color * (1 - reflectionFactor) +
                  reflectionColor * reflectionFactor;
  }

  return pixel_color;
}

void Scene::renderScene(int width, int height, int startWidth, int endWidth,
                        int startHeight, int endHeight, std::atomic<int> &done,
                        Image *image) {
  float width_chunk_size = width / 6.0f;
  float height_chunk_size = height / 6.0f;


  for (int y = startHeight; y < endHeight; y++) {
    for (int x = startWidth; x < endWidth; x++) {

      int current_chunk_x = std::floor(x / width_chunk_size);
      int current_chunk_y = std::floor(y / height_chunk_size);

      LightIntensity pixel_color;

      for (int s = 0; s < camera->samplesCount; s++) {
        math::ray ray = camera->generateRay(x, y, width, height);
        pixel_color =
            pixel_color + shade(ray, this->lights, this->objects, this->camera,
                                *this->colors[current_chunk_x][current_chunk_y],
                                0, this->maxDepth);
      }
      pixel_color = pixel_color / camera->samplesCount;
      image->setPixel(x, y, pixel_color);

      done += 1;
    }
  }

}
