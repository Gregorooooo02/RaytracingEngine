#include "mat4x4.h"
#include "mat3x3.h"

using namespace math;

mat4x4::mat4x4() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] = 0;
        }
    }
}

mat4x4::mat4x4(float a, float b, float c, float d,
               float e, float f, float g, float h,
               float i, float j, float k, float l,
               float m, float n, float o, float p) {
    float temp[4][4] = {
        {a, b, c, d},
        {e, f, g, h},
        {i, j, k, l},
        {m, n, o, p}
    };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] = temp[i][j];
        }
    }
}

mat4x4::~mat4x4() {}

mat4x4& mat4x4::operator=(const mat4x4& m) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] = m.data[i][j];
        }
    }
    return *this;
}

void mat4x4::add(const mat4x4& m) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] += m.data[i][j];
        }
    }
}

void mat4x4::subtract(const mat4x4& m) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] -= m.data[i][j];
        }
    }
}

void mat4x4::multiply(const mat4x4& m) {
    float temp[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                temp[i][j] += data[i][k] * m.data[k][j];
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] = temp[i][j];
        }
    }
}

void mat4x4::multiply(float scalar) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] *= scalar;
        }
    }
}

void mat4x4::divide(float scalar) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] /= scalar;
        }
    }
}

mat4x4 mat4x4::createIdentity() {
    mat4x4 identity;
    for (int i = 0; i < 4; i++) {
        identity.data[i][i] = 1;
    }
    return identity;
}

void mat4x4::inverse() {
    float det = determinant(*this);
    if (det == 0) {
        return;
    }
    
    float temp[4][4];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float minor[3][3];
            int mi = 0;
            for (int m = 0; m < 4; m++) {
                if (m == i) continue;
                int mj = 0;
                for (int n = 0; n < 4; n++) {
                    if (n == j) continue;
                    minor[mi][mj] = data[m][n];
                    mj++;
                }
                mi++;
            }
            float minor_det = determinant3x3(minor);
            float cofactor = ((i + j) % 2 == 0 ? 1.0f : -1.0f) * minor_det;
            
            temp[j][i] = cofactor / det;
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] = temp[i][j];
        }
    }
}

void mat4x4::transpose() {
    float temp[4][4] = {
        {data[0][0], data[1][0], data[2][0], data[3][0]},
        {data[0][1], data[1][1], data[2][1], data[3][1]},
        {data[0][2], data[1][2], data[2][2], data[3][2]},
        {data[0][3], data[1][3], data[2][3], data[3][3]}
    };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] = temp[i][j];
        }
    }
}

float mat4x4::determinant(mat4x4& m) {
    float det = 0;

    for (int i = 0; i < 4; i++) {
        det += (m.data[0][i] * (m.data[1][(i + 1) % 4] * (m.data[2][(i + 2) % 4] * m.data[3][(i + 3) % 4] 
        - m.data[2][(i + 3) % 4] * m.data[3][(i + 2) % 4]) 
        - m.data[1][(i + 2) % 4] * (m.data[2][(i + 1) % 4] * m.data[3][(i + 3) % 4] 
        - m.data[2][(i + 3) % 4] * m.data[3][(i + 1) % 4]) 
        + m.data[1][(i + 3) % 4] * (m.data[2][(i + 1) % 4] * m.data[3][(i + 2) % 4] 
        - m.data[2][(i + 2) % 4] * m.data[3][(i + 1) % 4])));
    }

    return det;
}

float mat4x4::determinant3x3(float m[3][3]) {
    float det = 0;

    for (int i = 0; i < 3; i++) {
        det += (m[0][i] * (m[1][(i + 1) % 3] * m[2][(i + 2) % 3] - 
        m[1][(i + 2) % 3] * m[2][(i + 1) % 3]));
    }

    return det;
}