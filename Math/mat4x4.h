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
            mat4x4 translate(const vec3&);
            mat4x4 scale(const vec3&);
            mat4x4 scale(const float);
            mat4x4 rotate(float, vec3&);
            // Additional rotation methods
            mat4x4 rotateX(const float);
            mat4x4 rotateY(const float);
            mat4x4 rotateZ(const float);
        private:
            float determinant(mat4x4&);
            float determinant3x3(float[3][3]);

    };
} // namespace math
