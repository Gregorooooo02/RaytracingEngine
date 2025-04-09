#include "plane.h"
#include <cmath>

using namespace math;

plane::plane() {
    this->a = 0.0f;
    this->b = 0.0f;
    this->c = 0.0f;
    this->d = 0.0f;
    this->normal = vec3();
    this->material = Material();
}

plane::plane(float a, float b, float c, float d, Material &material) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->normal = vec3(a, b, c);
    this->material = material;
}

plane::plane(const vec3& normal, float d, Material &material) {
    this->a = normal.x;
    this->b = normal.y;
    this->c = normal.z;
    this->d = d;
    this->normal = normal;
    this->material = material;
}

plane::plane(vec3& normal, vec3& point, Material &material) {
    this->a = normal.x;
    this->b = normal.y;
    this->c = normal.z;
    this->d = -normal.dotProduct(point);
    this->normal = normal;
    this->point = point;
    this->material = material;
}

plane::plane(vec3& p1, vec3& p2, vec3& p3, Material &material) {
    vec3 temp = p3.substract(p1);
    this->normal = (p2.substract(p1)).crossProduct(temp).normalize();
    this->a = this->normal.x;
    this->b = this->normal.y;
    this->c = this->normal.z;
    this->d = -this->normal.dotProduct(p1);
    this->point = p1;
    this->material = material;
}

plane::plane(const plane& plane) {
    this->a = plane.a;
    this->b = plane.b;
    this->c = plane.c;
    this->d = plane.d;
    this->normal = plane.normal;
    this->point = plane.point;
    this->material = plane.material;
}

plane::~plane() {}

vec3* plane::hit(ray& ray) {
    const float EPSILON = 1e-6f;
    float denominator = this->normal.dotProduct(ray.d);
    if (fabs(denominator) < EPSILON) {
        return nullptr;
    }

    float t = -(this->normal.dotProduct(ray.o) + this->d) / denominator;
    if (t < denominator) {
        return nullptr;
    }

    vec3 result = ray.point_at(t);
    vec3* resultPtr = new vec3(result);
    return resultPtr;
}

vec3 plane::getNormal(vec3 point) {
    return this->normal;
}
