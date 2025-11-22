#include "Math3D/Matrix3.h"
#include <cstring>

namespace Math3D {

Matrix3::Matrix3() {
    std::memset(m, 0, 9 * sizeof(float));
}

Matrix3::Matrix3(const float data[9]) {
    std::memcpy(m, data, 9 * sizeof(float));
}

float& Matrix3::operator()(int row, int col) {
    return m[col * 3 + row];
}

float Matrix3::operator()(int row, int col) const {
    return m[col * 3 + row];
}

Matrix3 Matrix3::Transposed() const {
    Matrix3 result;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            result(row, col) = (*this)(col, row);
        }
    }
    return result;
}

Matrix3 Matrix3::operator*(const Matrix3& other) const {
    Matrix3 result;
    for (int col = 0; col < 3; ++col) {
        for (int row = 0; row < 3; ++row) {
            float sum = 0.0f;
            for (int k = 0; k < 3; ++k) {
                sum += (*this)(row, k) * other(k, col);
            }
            result(row, col) = sum;
        }
    }
    return result;
}

Vector3 Matrix3::operator*(const Vector3& vector) const {
    return Vector3(
        m[0] * vector.x + m[3] * vector.y + m[6] * vector.z,
        m[1] * vector.x + m[4] * vector.y + m[7] * vector.z,
        m[2] * vector.x + m[5] * vector.y + m[8] * vector.z
    );
}

Matrix3 Matrix3::Identity() {
    Matrix3 result;
    result(0, 0) = 1.0f;
    result(1, 1) = 1.0f;
    result(2, 2) = 1.0f;
    return result;
}

} 
