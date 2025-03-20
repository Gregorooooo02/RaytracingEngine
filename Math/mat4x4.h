#pragma once

#include "vec3.h"

namespace math {
    class mat4x4 {
        public:
            float data[4][4];

            mat4x4();
            mat4x4(float, float, float, float,
                float, float, float, float,
                float, float, float, float,
                float, float, float, float);
            ~mat4x4();
            mat4x4& operator=(const mat4x4&);
            
            // Operations
            void add(const mat4x4&);
            void subtract(const mat4x4&);
            void multiply(const mat4x4&);
            void multiply(float);
            void divide(float);

            static mat4x4 createIdentity();

            void inverse();
            void transpose();

            // Transformations
            void translate(const vec3&);
            void scale(const vec3&);
            void scale(const float);
            void rotate(float, vec3&);
            // Additional rotation methods
            void rotateX(const float);
            void rotateY(const float);
            void rotateZ(const float);
        private:
            float determinant(mat4x4&);
            float determinant3x3(float[3][3]);

    };
} // namespace math