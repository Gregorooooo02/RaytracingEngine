#include "vec3.h"
#include "mat3x3.h"
#include "mat4x4.h"
#include "quaternion.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "ray.h"

#include <iostream>
#include <cmath>

void printMatrix(math::mat3x3& m);
void printMatrix_4x4(math::mat4x4 m);

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
    math::vec3 dir1 = center.substract(origin).normalize();
    math::ray r1(origin, dir1);

    math::vec3 ress = origin.crossProduct(dir1);

    // Ex 9 - define a ray with origin in (0, 0, -20) and direction parallel to the Y axis
    math::vec3 dir2(0, 1, 0);
    math::ray r2(origin, dir2);

    // Ex 10 & 11 - check if the r1 and r2 rays hit the s1 sphere
    std::cout << "R1:" << std::endl;
    bool hit1 = s1.hit(r1, 0, 10.00001f);
    std::cout << "R2:" << std::endl;
    bool hit2 = s1.hit(r2, 0, 1000000);

    // Ex 12 - define a ray that has only one hit point with the s1 sphere
    math::vec3 dir3(0, 0, 1);
    math::vec3 origin2(0, 10, -20);
    math::ray r3(origin2, dir3);

    std::cout << "R3:" << std::endl;
    bool hit3 = s1.hit(r3, 0, 20.001f);

    // Ex 13 - define a plane that intersects with a point (0, 0, 0) and has a normal vector 45 degrees to the axis Y and Z
    math::vec3 point(0, 0, 0);
    float angle_p = static_cast<float>(cos(45 * M_PI / 180));
    math::vec3 normal(0, angle_p, angle_p);
    math::plane p1(normal, point);

    // Ex 14 - define a ray that hits the plane from ex 13
    std::cout << "P1:" << std::endl;
    bool hit4 = p1.hit(r2);

    // Ex 15 - przypadek 1
    math::vec3 a(0, 0, 0);
    math::vec3 b(1, 0, 0);
    math::vec3 c(0, 1, 0);

    math::triangle t1(a, b, c);

    math::vec3 p1_o(-1.0f, 0.5f, 0.0f);
    math::vec3 p1_d(1.0f, 0.0f, 0.0f);
    math::ray r4(p1_o, p1_d);

    std::cout << "T1 - przypadek 1:" << std::endl;
    bool hit5 = t1.hit(r4);
    std::cout << "Hit: " << hit5 << std::endl;

    // Ex 15 - przypadek 2
    math::vec3 p2_o(2, -1, 0);
    math::vec3 p2_d(0, 1, 0);
    math::ray r5(p2_o, p2_d);

    std::cout << "T1 - przypadek 2:" << std::endl;
    bool hit6 = t1.hit(r5);
    std::cout << "Hit: " << hit6 << std::endl;

    // Ex 15 - przypadek 3
    math::vec3 p3_o(0, 1, -1);
    math::vec3 p3_d(0, 0, 1);
    math::ray r6(p3_o, p3_d);
    std::cout << "T1 - przypadek 3:" << std::endl;
    bool hit7 = t1.hit(r6);
    std::cout << "Hit: " << hit7 << std::endl;

    std::cout << std::endl;
    // Additional exercises!!
    // Ex 1 & 2 - check if all the matrices methods work correctly
    math::mat3x3 m1(1, 2, 3,
                    4, 5, 6,
                    7, 8, 9);
    math::mat3x3 m2(1, 2, 3,
                    4, 5, 6,
                    7, 8, 9);

    std::cout << "Macierz m1 i m2:" << std::endl;
    printMatrix(m1);
    std::cout << std::endl;

    std::cout << "Dodawanie macierzy:" << std::endl;
    math::mat3x3 m3 = m1.add(m2);
    printMatrix(m3);
    std::cout << std::endl;
    std::cout << "Odejmowanie macierzy:" << std::endl;
    math::mat3x3 m4 = m1.subtract(m2);
    printMatrix(m4);
    std::cout << std::endl;
    std::cout << "Mnożenie macierzy:" << std::endl;
    math::mat3x3 m5 = m1.multiply(m2);
    printMatrix(m5);
    std::cout << std::endl;
    std::cout << "Mnożenie macierzy przez skalar:" << std::endl;
    math::mat3x3 m6 = m1.multiply(2);
    printMatrix(m6);
    std::cout << std::endl;
    std::cout << "Dzielenie macierzy przez skalar:" << std::endl;
    math::mat3x3 m7 = m1.divide(2);
    printMatrix(m7);
    std::cout << std::endl;

    std::cout << "Macierz jednostkowa:" << std::endl;
    math::mat3x3 m8 = math::mat3x3::createIdentity();
    printMatrix(m8);
    std::cout << std::endl;

    std::cout << "Transpozycja macierzy:" << std::endl;
    m1.transpose();
    printMatrix(m1);
    std::cout << std::endl;

    std::cout << "Odwrotność macierzy:" << std::endl;
    math::mat3x3 m9(1, 2, 3,
                    0, 1, 4,
                    5, 6, 0);
    m9.inverse();
    printMatrix(m9);
    std::cout << std::endl << std::endl;

    std::cout << "Macierz 4x4:\n";

    math::mat4x4 m4_1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    math::mat4x4 m4_2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    printMatrix_4x4(m4_1);


    std::cout << "\n";

    std::cout << "Dodawanie macierzy: \n";
    m4_1.add(m4_2);
    printMatrix_4x4(m4_1);
    m4_1 = math::mat4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    std::cout << "\n\n";

    std::cout << "Odejmowanie macierzy: \n";
    m4_1.subtract(m4_2);
    printMatrix_4x4(m4_1);
    m4_1 = math::mat4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    std::cout << "\n\n";

    std::cout << "Mnozenie macierzy przez macierz: \n";
    m4_1.multiply(m4_2);
    printMatrix_4x4(m4_1);
    m4_1 = math::mat4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    std::cout << "\n\n";

    std::cout << "Mnozenie macierzy przez skalar: \n";
    m4_1.multiply(2.0f);
    printMatrix_4x4(m4_1);
    m4_1 = math::mat4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    std::cout << "\n\n";

    std::cout << "Dzielenie macierzy: \n";
    m4_1.divide(2.0f);
    printMatrix_4x4(m4_1);
    m4_1 = math::mat4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    std::cout << "\n\n";

    std::cout << "Macierz jednostkowa: \n";
    math::mat4x4 identity = m4_1.createIdentity();
    printMatrix_4x4(identity);
    std::cout << "\n\n";

    std::cout << "Macierz transponowana: \n";
    m4_1.transpose();
    printMatrix_4x4(m4_1);
    m4_1 = math::mat4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    std::cout << "\n\n";

    std::cout << "Macierz odwrotna: \n";
    m4_1.inverse();
    printMatrix_4x4(m4_1);
    m4_1 = math::mat4x4(1, 2, 7, 4, 5, 2, 7, 8, 9, 1, 11, 12, 3, 14, 6, 0);
    std::cout << "\n\n";

    std::cout << "Translacja macierzy: \n";
    math::mat4x4 translated = m4_1.translate(math::vec3(4, 2, 0));
    printMatrix_4x4(translated);
    std::cout << "\n\n";

    std::cout << "Skalowanie macierzy o wektor: \n";
    math::mat4x4 scaled = m4_1.scale(math::vec3(4, 2, 0));
    printMatrix_4x4(scaled);
    std::cout << "\n\n";

    std::cout << "Skalowanie macierzy o skalar: \n";
    scaled = m4_1.scale(8);
    printMatrix_4x4(scaled);
    std::cout << "\n\n";

    std::cout << "Obrocenie macierzy wzgledem osi o kat: \n";
    math::vec3 v(1, 0 ,0);
    math::mat4x4 rotated = m4_1.rotate(45, v);
    printMatrix_4x4(rotated);
    std::cout << "\n\n";

    std::cout << "Obrocenie macierzy wzgledem osi X: \n";
    rotated = m4_1.rotateX(45);
    printMatrix_4x4(rotated);
    std::cout << "\n\n";

    std::cout << "Obrocenie macierzy wzgledem osi Y: \n";
    rotated = m4_1.rotateY(45);
    printMatrix_4x4(rotated);
    std::cout << "\n\n";

    std::cout << "Obrocenie macierzy wzgledem osi Z: \n";
    rotated = m4_1.rotateZ(45);
    printMatrix_4x4(rotated);
    std::cout << "\n\n";

    // Ex 3 - Rotate the vector (1, 0, 0, 1) by 90 degrees around the Y axis
    math::mat4x4 mm(1, 0, 0, 1,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);

    math::mat4x4 mm2 = mm.rotateY(90);

    std::cout << "Obrót wektora (1, 0, 0, 1) o 90 stopni wokół osi Y:" << std::endl;
    printMatrix_4x4(mm2);


    // Ex 4 - Prove the lack of commutativity of matrix multiplication using an implemented example
    math::mat3x3 m10(1, 2, 3,
                    4, 5, 6,
                    7, 8, 9);
    math::mat3x3 m11(2, 0, 3,
                    4, 7, 6,
                    2, 1, 9);

    std::cout << "Mnożenie macierzy m10 i m11:" << std::endl;
    math::mat3x3 m12 = m10.multiply(m11);
    printMatrix(m12);

    std::cout << "Mnożenie macierzy m11 i m10:" << std::endl;
    math::mat3x3 m13 = m11.multiply(m10);
    printMatrix(m13);

    // Ex 5 - implement the quaternion class with its methods - DONE
    // Ex 6 - rotate the vector (3, 1, 3) around the vector (1, 0 ,1) by 90 degrees
    math::vec3 v7(3, 1, 3);
    math::vec3 axis(1, 0, 1);
    math::vec3 v7r = v7.rotate(90, axis);
    std::cout << "Wektor v7 po rotacji o 90 stopni wokół osi (1, 0, 1): " << v7r.x << ", " << v7r.y << ", " << v7r.z << std::endl;

    // Ex 7 - implement the quaternion to rotate by 30 degrees around the X axis; check its length, inverse
    math::vec3 v8(1, 0, 0);
    float angle2 = 30;
    float angleRad = angle2 * M_PI / 180.0f;
    math::quaternion q1(angleRad, v8);
    q1.convertToUnitNorm();
    std::cout << "Długość kwaternionu q1: " << q1.norm() << std::endl;
    math::quaternion q1i = q1.inverse();
    std::cout << "Kwaternion odwrotny do q1: " << q1i.s << ", " << q1i.v.x << ", " << q1i.v.y << ", " << q1i.v.z << std::endl;

    // Ex 8
    math::vec3 av(0.06f, -0.257f, -0.935f);
    math::quaternion q2(0.233f, av);
    math::vec3 bv(0.286f, 0.374f, 0.459f);
    math::quaternion q3(-0.752f, bv);

    // Dot product of q2 and q3
    float dot = q2.s * q3.s + q2.v.dotProduct(q3.v);
    std::cout << "Iloczyn skalarny a i b: " << dot << std::endl;

    // Quaternion multiplication
    math::quaternion q4 = q2.multiply(q3);
    std::cout << "Iloczyn a i b: " << q4.s << ", " << q4.v.x << ", " << q4.v.y << ", " << q4.v.z << std::endl;

    // Subtract q3 from q2
    math::quaternion q5 = q2.substract(q3);
    std::cout << "Odejmowanie a i b: " << q5.s << ", " << q5.v.x << ", " << q5.v.y << ", " << q5.v.z << std::endl;

    return 0;
}

void printMatrix(math::mat3x3& m) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << m.data[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

void printMatrix_4x4(math::mat4x4 m) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << m.data[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}