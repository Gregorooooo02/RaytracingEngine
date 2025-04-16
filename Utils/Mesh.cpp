#include "Mesh.h"
#include "objectLoader.h"

#include <cmath>

using namespace math;

vec3 rotateVector(const vec3 &v, const vec3 &rotation);

Mesh::Mesh(const std::string &filename, vec3 &translation, float scale, vec3 &rotation, Material &material) {
  ObjectLoader loader;
  if (!loader.loadObject(filename, material)) {
    std::cerr << "Failed to load object file: " << filename << std::endl;
    return;
  }

  for (auto &tri : loader.faces) {
    vec3 v1 = rotateVector(tri.vertices[0] * scale, rotation) + translation;
    vec3 v2 = rotateVector(tri.vertices[1] * scale, rotation) + translation;
    vec3 v3 = rotateVector(tri.vertices[2] * scale, rotation) + translation;

    auto *t = new triangle(v1, v2, v3, material);
    triangles.push_back(t);
  }
}

Mesh::~Mesh() {
  for (const auto &tri : triangles) {
    delete tri;
  }
}

vec3* Mesh::hit(ray &ray) {
  float closestT = std::numeric_limits<float>::max();
  vec3 *closestHit = nullptr;

  for (const auto &tri : triangles) {
    vec3 *hitPoint = tri->hit(ray);
    if (hitPoint) {
      float t = (*hitPoint - ray.o).len();
      if (t < closestT) {
        closestT = t;
        closestHit = std::move(hitPoint);
      }
    }
  }
  return closestHit;
}

vec3 Mesh::getNormal(vec3 point) {
  if (!triangles.empty()) {
    return triangles[0]->getNormal(point);
  }
  return {0, 0, 0}; // Default normal if no triangles are present
}

vec3 rotateVector(const vec3 &v, const vec3 &rotation) {
  float cosX = cos(rotation.x);
  float sinX = sin(rotation.x);
  vec3 vX = vec3(
    v.x,
    v.y * cosX - v.z * sinX,
    v.y * sinX + v.z * cosX
  );

  float cosY = cos(rotation.y);
  float sinY = sin(rotation.y);
  vec3 vY = vec3(
    vX.z * sinY + vX.x * cosY,
    vX.y,
    vX.z * cosY - vX.x * sinY
  );

  float cosZ = cos(rotation.z);
  float sinZ = sin(rotation.z);
  vec3 vZ = vec3(
    vY.x * cosZ - vY.y * sinZ,
    vY.x * sinZ + vY.y * cosZ,
    vY.z
  );

  return vZ;
}