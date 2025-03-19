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

            inline void add(const mat3x3&);
            inline void subtract(const mat3x3&);
            inline void multiply(const mat3x3&);
            inline void multiply(float);
            inline void divide(float);

            static mat3x3 createIdentity();
            
            inline void inverse();
            inline void transpose();
        private:
            float determinant(mat3x3&);
    };
} // namespace math