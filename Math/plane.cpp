#include "plane.h"

using namespace math;

plane::plane() {
    this->a = 0.0f;
    this->b = 0.0f;
    this->c = 0.0f;
    this->d = 0.0f;
    this->normal = vec3();
}

plane::plane(float a, float b, float c, float d) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->normal = vec3(a, b, c);
}

plane::plane(const vec3& normal, float d) {
    this->a = normal.x;
    this->b = normal.y;
    this->c = normal.z;
    this->d = d;
    this->normal = normal;
}

plane::plane(vec3& normal, vec3& point) {
    this->a = normal.x;
    this->b = normal.y;
    this->c = normal.z;
    this->d = -normal.dotProduct(point);
    this->normal = normal;
    this->point = point;
}

plane::plane(const plane& plane) {
    this->a = plane.a;
    this->b = plane.b;
    this->c = plane.c;
    this->d = plane.d;
    this->normal = plane.normal;
    this->point = plane.point;
}

plane::~plane() {}

bool plane::hit(ray& ray) {
    float denominator = this->normal.dotProduct(ray.d);
    if (denominator == 0) {
        return false;
    }

    float t = -(this->normal.dotProduct(ray.o) + this->d) / denominator;

    return t >= 0;
}