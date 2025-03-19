#pragma once

namespace math {
    class mat3x3 {
        public:
            float data[3][3];

            mat3x3();
            mat3x3(float, float, float,
                   float, float, float,
                   float, float, float);
            ~mat3x3();
            mat3x3& operator=(const mat3x3&);

            void add(const mat3x3&);
            void subtract(const mat3x3&);
            void multiply(const mat3x3&);
            void multiply(float);
            void divide(float);

            static mat3x3 createIdentity();
            
            void inverse();
            void transpose();

            float determinant(mat3x3&);
    };
} // namespace math