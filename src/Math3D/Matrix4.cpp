#include "Math3D/Matrix4.h"
#include "Math3D/MathUtils.h"
#include <cmath>
#include <cstring>

namespace Math3D {

Matrix4::Matrix4() {
    std::memset(m, 0, 16 * sizeof(float));
}

Matrix4::Matrix4(const float data[16]) {
    std::memcpy(m, data, 16 * sizeof(float));
}

float& Matrix4::operator()(int row, int col) {
    return m[col * 4 + row];
}

float Matrix4::operator()(int row, int col) const {
    return m[col * 4 + row];
}

Matrix4 Matrix4::operator+(const Matrix4& other) const {
    Matrix4 result;
    for (int i = 0; i < 16; ++i) {
        result.m[i] = m[i] + other.m[i];
    }
    return result;
}

Matrix4 Matrix4::operator-(const Matrix4& other) const {
    Matrix4 result;
    for (int i = 0; i < 16; ++i) {
        result.m[i] = m[i] - other.m[i];
    }
    return result;
}

Matrix4 Matrix4::operator*(const Matrix4& other) const {
    Matrix4 result;
    for (int col = 0; col < 4; ++col) {
        for (int row = 0; row < 4; ++row) {
            float sum = 0.0f;
            for (int k = 0; k < 4; ++k) {
                sum += (*this)(row, k) * other(k, col);
            }
            result(row, col) = sum;
        }
    }
    return result;
}

Vector4 Matrix4::operator*(const Vector4& vector) const {
    return Vector4(
        m[0] * vector.x + m[4] * vector.y + m[8] * vector.z + m[12] * vector.w,
        m[1] * vector.x + m[5] * vector.y + m[9] * vector.z + m[13] * vector.w,
        m[2] * vector.x + m[6] * vector.y + m[10] * vector.z + m[14] * vector.w,
        m[3] * vector.x + m[7] * vector.y + m[11] * vector.z + m[15] * vector.w
    );
}

Matrix4 Matrix4::operator*(float scalar) const {
    Matrix4 result;
    for (int i = 0; i < 16; ++i) {
        result.m[i] = m[i] * scalar;
    }
    return result;
}

Matrix4& Matrix4::operator+=(const Matrix4& other) {
    for (int i = 0; i < 16; ++i) {
        m[i] += other.m[i];
    }
    return *this;
}

Matrix4& Matrix4::operator-=(const Matrix4& other) {
    for (int i = 0; i < 16; ++i) {
        m[i] -= other.m[i];
    }
    return *this;
}

Matrix4& Matrix4::operator*=(const Matrix4& other) {
    *this = *this * other;
    return *this;
}

Matrix4& Matrix4::operator*=(float scalar) {
    for (int i = 0; i < 16; ++i) {
        m[i] *= scalar;
    }
    return *this;
}

bool Matrix4::operator==(const Matrix4& other) const {
    for (int i = 0; i < 16; ++i) {
        if (!MathUtils::Approximately(m[i], other.m[i])) {
            return false;
        }
    }
    return true;
}

bool Matrix4::operator!=(const Matrix4& other) const {
    return !(*this == other);
}

Matrix4 Matrix4::Transposed() const {
    Matrix4 result;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result(row, col) = (*this)(col, row);
        }
    }
    return result;
}

float Matrix4::Determinant() const {
    float det = 0.0f;
    det += m[0] * (m[5] * (m[10] * m[15] - m[11] * m[14]) - 
                   m[6] * (m[9] * m[15] - m[11] * m[13]) + 
                   m[7] * (m[9] * m[14] - m[10] * m[13]));
    
    det -= m[1] * (m[4] * (m[10] * m[15] - m[11] * m[14]) - 
                   m[6] * (m[8] * m[15] - m[11] * m[12]) + 
                   m[7] * (m[8] * m[14] - m[10] * m[12]));
    
    det += m[2] * (m[4] * (m[9] * m[15] - m[11] * m[13]) - 
                   m[5] * (m[8] * m[15] - m[11] * m[12]) + 
                   m[7] * (m[8] * m[13] - m[9] * m[12]));
    
    det -= m[3] * (m[4] * (m[9] * m[14] - m[10] * m[13]) - 
                   m[5] * (m[8] * m[14] - m[10] * m[12]) + 
                   m[6] * (m[8] * m[13] - m[9] * m[12]));
    
    return det;
}

Matrix4 Matrix4::Inverted() const {
    // Have not implemented full inversion yet 
    return Identity();
}

Matrix4 Matrix4::Identity() {
    Matrix4 result;
    result(0, 0) = 1.0f;
    result(1, 1) = 1.0f;
    result(2, 2) = 1.0f;
    result(3, 3) = 1.0f;
    return result;
}

Matrix4 Matrix4::Translation(const Vector3& translation) {
    Matrix4 result = Identity();
    result(0, 3) = translation.x;
    result(1, 3) = translation.y;
    result(2, 3) = translation.z;
    return result;
}

Matrix4 Matrix4::Scaling(const Vector3& scale) {
    Matrix4 result = Identity();
    result(0, 0) = scale.x;
    result(1, 1) = scale.y;
    result(2, 2) = scale.z;
    return result;
}

Matrix4 Matrix4::RotationX(float angle) {
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);
    
    Matrix4 result = Identity();
    result(1, 1) = cosA;
    result(1, 2) = -sinA;
    result(2, 1) = sinA;
    result(2, 2) = cosA;
    return result;
}

Matrix4 Matrix4::RotationY(float angle) {
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);
    
    Matrix4 result = Identity();
    result(0, 0) = cosA;
    result(0, 2) = sinA;
    result(2, 0) = -sinA;
    result(2, 2) = cosA;
    return result;
}

Matrix4 Matrix4::RotationZ(float angle) {
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);
    
    Matrix4 result = Identity();
    result(0, 0) = cosA;
    result(0, 1) = -sinA;
    result(1, 0) = sinA;
    result(1, 1) = cosA;
    return result;
}

Matrix4 Matrix4::Perspective(float fov, float aspect, float near, float far) {
    float tanHalfFov = std::tan(fov / 2.0f);
    
    Matrix4 result;
    result(0, 0) = 1.0f / (aspect * tanHalfFov);
    result(1, 1) = 1.0f / tanHalfFov;
    result(2, 2) = -(far + near) / (far - near);
    result(2, 3) = -1.0f;
    result(3, 2) = -(2.0f * far * near) / (far - near);
    result(3, 3) = 0.0f;
    
    return result;
}

Matrix4 Matrix4::Orthographic(float left, float right, float bottom, float top, float near, float far) {
    Matrix4 result = Identity();
    result(0, 0) = 2.0f / (right - left);
    result(1, 1) = 2.0f / (top - bottom);
    result(2, 2) = -2.0f / (far - near);
    result(0, 3) = -(right + left) / (right - left);
    result(1, 3) = -(top + bottom) / (top - bottom);
    result(2, 3) = -(far + near) / (far - near);
    return result;
}

Matrix4 Matrix4::LookAt(const Vector3& eye, const Vector3& target, const Vector3& up) {
    Vector3 z = (eye - target).Normalized();
    Vector3 x = up.Cross(z).Normalized();
    Vector3 y = z.Cross(x);
    
    Matrix4 result = Identity();
    result(0, 0) = x.x; result(0, 1) = x.y; result(0, 2) = x.z;
    result(1, 0) = y.x; result(1, 1) = y.y; result(1, 2) = y.z;
    result(2, 0) = z.x; result(2, 1) = z.y; result(2, 2) = z.z;
    result(0, 3) = -x.Dot(eye);
    result(1, 3) = -y.Dot(eye);
    result(2, 3) = -z.Dot(eye);
    
    return result;
}

Matrix4 operator*(float scalar, const Matrix4& matrix) {
    return matrix * scalar;
}

} 
