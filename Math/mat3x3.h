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

            mat3x3 add(const mat3x3&);
            mat3x3 subtract(const mat3x3&);
            mat3x3 multiply(const mat3x3&);
            mat3x3 multiply(float);
            mat3x3 divide(float);

            static mat3x3 createIdentity();
            
            void inverse();
            void transpose();

            float determinant(mat3x3&);
    };
} // namespace math