#include "triangle.h"
#include "plane.h"

using namespace math;

triangle::triangle() {
    for (int i = 0; i < 3; i++) {
        this->vertices[i] = vec3();
        this->normals[i] = vec3();
    }
}

triangle::triangle(vec3& v1, vec3& v2, vec3& v3) {
    this->vertices[0] = v1;
    this->vertices[1] = v2;
    this->vertices[2] = v3;
}

triangle::triangle(vec3& v1, vec3& v2, vec3& v3, vec3& n1, vec3& n2, vec3& n3) {
    this->vertices[0] = v1;
    this->vertices[1] = v2;
    this->vertices[2] = v3;

    this->normals[0] = n1;
    this->normals[1] = n2;
    this->normals[2] = n3;
}

triangle::~triangle() {}

triangle::triangle(const triangle& t) {
    for (int i = 0; i < 3; i++) {
        this->vertices[i] = t.vertices[i];
        this->normals[i] = t.normals[i];
    }
}

bool triangle::hit(ray& ray) {
    // Getting the normal of the triangle
    vec3 normal = (this->vertices[1].substract(this->vertices[0])).crossProduct(this->vertices[2].substract(this->vertices[0])).normalize();

    float d = -normal.dotProduct(this->vertices[0]);

    float t = -(normal.dotProduct(ray.o) + d) / normal.dotProduct(ray.d);

    if (t < 0) {
        return false;
    }

    vec3 hitPoint = ray.o.add(ray.d.multiply(t));
    vec3 ne;

    // Testing edge 0 of the triangle
    vec3 v0p = hitPoint.substract(this->vertices[0]);
    vec3 v1v0 = this->vertices[1].substract(this->vertices[0]);
    ne = v1v0.crossProduct(v0p);
    if (normal.dotProduct(ne) < 0) {
        return false;
    }

    // Testing edge 1 of the triangle
    vec3 v1p = hitPoint.substract(this->vertices[1]);
    vec3 v2v1 = this->vertices[2].substract(this->vertices[1]);
    ne = v2v1.crossProduct(v1p);
    if (normal.dotProduct(ne) < 0) {
        return false;
    }

    // Testing edge 2 of the triangle
    vec3 v2p = hitPoint.substract(this->vertices[2]);
    vec3 v0v2 = this->vertices[0].substract(this->vertices[2]);
    ne = v0v2.crossProduct(v2p);
    if (normal.dotProduct(ne) < 0) {
        return false;
    }

    return true;
}