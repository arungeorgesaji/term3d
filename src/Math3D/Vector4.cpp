#include "Math3D/Vector4.h"
#include "Math3D/Vector3.h"
#include <cmath>

namespace Math3D {

Vector4::Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
Vector4::Vector4(const Vector3& xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

Vector4 Vector4::operator+(const Vector4& other) const {
    return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4 Vector4::operator-(const Vector4& other) const {
    return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4 Vector4::operator*(float scalar) const {
    return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

Vector4 Vector4::operator/(float scalar) const {
    float invScalar = 1.0f / scalar;
    return Vector4(x * invScalar, y * invScalar, z * invScalar, w * invScalar);
}

Vector4& Vector4::operator+=(const Vector4& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

Vector4& Vector4::operator-=(const Vector4& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

Vector4& Vector4::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

Vector4& Vector4::operator/=(float scalar) {
    float invScalar = 1.0f / scalar;
    x *= invScalar;
    y *= invScalar;
    z *= invScalar;
    w *= invScalar;
    return *this;
}

bool Vector4::operator==(const Vector4& other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Vector4::operator!=(const Vector4& other) const {
    return !(*this == other);
}

float Vector4::Dot(const Vector4& other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

float Vector4::Length() const {
    return std::sqrt(LengthSquared());
}

float Vector4::LengthSquared() const {
    return x * x + y * y + z * z + w * w;
}

Vector4 Vector4::Normalized() const {
    float len = Length();
    if (len > 0.0f) {
        return *this / len;
    }
    return Zero;
}

void Vector4::Normalize() {
    float len = Length();
    if (len > 0.0f) {
        *this /= len;
    }
}

Vector3 Vector4::XYZ() const {
    return Vector3(x, y, z);
}

const Vector4 Vector4::Zero(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::One(1.0f, 1.0f, 1.0f, 1.0f);

Vector4 operator*(float scalar, const Vector4& vector) {
    return vector * scalar;
}

} 
