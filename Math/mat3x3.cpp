#include "mat3x3.h"

using namespace math;

mat3x3::mat3x3() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            data[i][j] = 0;
        }
    }
}

mat3x3::mat3x3(float a, float b, float c,
               float d, float e, float f,
               float g, float h, float i) {
    float temp[3][3] = {
        {a, b, c},
        {d, e, f},
        {g, h, i}
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            data[i][j] = temp[i][j];
        }
    }
}

mat3x3::~mat3x3() {}

mat3x3& mat3x3::operator=(const mat3x3& m) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            data[i][j] = m.data[i][j];
        }
    }
    return *this;
}

mat3x3 mat3x3::add(const mat3x3& m) {
    mat3x3 result = *this;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.data[i][j] += m.data[i][j];
        }
    }
    return result;
}

mat3x3 mat3x3::subtract(const mat3x3& m) {
    mat3x3 result = *this;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.data[i][j] -= m.data[i][j];
        }
    }
    return result;
}

mat3x3 mat3x3::multiply(const mat3x3& m) {
    mat3x3 result = *this;
    float temp[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                temp[i][j] += result.data[i][k] * m.data[k][j];
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.data[i][j] = temp[i][j];
        }
    }
    return result;
}

mat3x3 mat3x3::multiply(float scalar) {
    mat3x3 result = *this;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.data[i][j] *= scalar;
        }
    }
    return result;
}

mat3x3 mat3x3::divide(float scalar) {
    mat3x3 result = *this;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.data[i][j] /= scalar;
        }
    }
    return result;
}

mat3x3 mat3x3::createIdentity() {
    return mat3x3(1, 0, 0,
                  0, 1, 0,
                  0, 0, 1);
}

void mat3x3::inverse() {
    float det = determinant(*this);
    if (det == 0) {
        return;
    }

    float temp[3][3] = {
        {data[1][1] * data[2][2] - data[1][2] * data[2][1], data[0][2] * data[2][1] - data[0][1] * data[2][2], data[0][1] * data[1][2] - data[0][2] * data[1][1]},
        {data[1][2] * data[2][0] - data[1][0] * data[2][2], data[0][0] * data[2][2] - data[0][2] * data[2][0], data[0][2] * data[1][0] - data[0][0] * data[1][2]},
        {data[1][0] * data[2][1] - data[1][1] * data[2][0], data[0][1] * data[2][0] - data[0][0] * data[2][1], data[0][0] * data[1][1] - data[0][1] * data[1][0]}
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            data[i][j] = temp[i][j] / det;
        }
    }
}

void mat3x3::transpose() {
    float temp[3][3] = {
        {data[0][0], data[1][0], data[2][0]},
        {data[0][1], data[1][1], data[2][1]},
        {data[0][2], data[1][2], data[2][2]}
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            data[i][j] = temp[i][j];
        }
    }
}

float mat3x3::determinant(mat3x3& m) {
    float det = 0;

    for (int i = 0; i < 3; i++) {
        det += (m.data[0][i] * (m.data[1][(i + 1) % 3] * m.data[2][(i + 2) % 3] - 
        m.data[1][(i + 2) % 3] * m.data[2][(i + 1) % 3]));
    }

    return det;
}
