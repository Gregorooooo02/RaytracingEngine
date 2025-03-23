#include "vec3.h"
#include "sphere.h"
#include "ray.h"

#include <iostream>
#include <cmath>

int main() {

  // Ex 1 & 2
  math::vec3 v1(1, 2, 3);
  math::vec3 v2(4, 5, 6);

  math::vec3 v12 = v1.add(v2);
  v1 = math::vec3(1, 2, 3);
  math::vec3 v21 = v2.add(v1);

  std::cout << "Przemienność dodawania wektorów:" << std::endl;
  std::cout << "v1 + v2 = " << v12.x << ", " << v12.y << ", " << v12.z << std::endl;
  std::cout << "v2 + v1 = " << v21.x << ", " << v21.y << ", " << v21.z << std::endl;

  // Ex 3 - find the degree between two vectors
  math::vec3 v3(0, 3, 0);
  math::vec3 v4(5, 5, 0);

  float v34 = v3.dotProduct(v4);
  v34 = v34 / (v3.len() * v4.len());
  float angle = acos(v34) * 180 / M_PI;

  std::cout << "Kąt między v3 i v4: " << angle << std::endl;

  // Ex 4 - find the vector that is perpendicular to two vectors
  math::vec3 v5(4, 5, 1);
  math::vec3 v6(4, 1, 3);

  math::vec3 v56 = v5.crossProduct(v6);
  std::cout << "Wektor prostopadły do v5 i v6: " << v56.x << ", " << v56.y << ", " << v56.z << std::endl;

  // Ex 5 - normalize a vector from ex 4
  math::vec3 v56n = v56.normalize();
  std::cout << "Wektor prostopadły do v5 i v6 znormalizowany: " << v56n.x << ", " << v56n.y << ", " << v56n.z << std::endl;

  // Ex 7 - define a sphere with a center in (0, 0, 0) and radius 10
  math::vec3 center(0, 0, 0);
  math::sphere s1(center, 10);

  // Ex 8 - define a ray with origin in (0, 0, -20) and direction (0, 0, 0);
  math::vec3 origin(0, 0, -20);
  math::ray r1(origin, center);

  // Ex 9 - define a ray with origin in (0, 0, -20) and direction parallel to the Y axis
  math::vec3 direction(0, 1, 0);
  math::ray r2(origin, direction);

  // Ex 10 - check if the r1 and r2 rays hit the s1 sphere
  bool hit1 = s1.hit(r1);
  bool hit2 = s1.hit(r2);

  std::cout << "Czy r1 trafia w s1: " << hit1 << std::endl;
  std::cout << "Czy r2 trafia w s1: " << hit2 << std::endl;

  return 0;
}
