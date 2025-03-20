#pragma once

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

            void add(const mat4x4&);
            void subtract(const mat4x4&);
            void multiply(const mat4x4&);
            void multiply(float);
            void divide(float);

            static mat4x4 createIdentity();

            void inverse();
            void transpose();
        private:
            float determinant(mat4x4&);
            float determinant3x3(float[3][3]);

    };
} // namespace math