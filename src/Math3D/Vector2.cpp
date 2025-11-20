#include "Math3D/Vector2.h"
#include <cmath>

namespace Math3D {

Vector2::Vector2() : x(0.0f), y(0.0f) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(float scalar) const {
    float invScalar = 1.0f / scalar;
    return Vector2(x * invScalar, y * invScalar);
}

Vector2& Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2& Vector2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2& Vector2::operator/=(float scalar) {
    float invScalar = 1.0f / scalar;
    x *= invScalar;
    y *= invScalar;
    return *this;
}

bool Vector2::operator==(const Vector2& other) const {
    return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2& other) const {
    return !(*this == other);
}

float Vector2::Dot(const Vector2& other) const {
    return x * other.x + y * other.y;
}

float Vector2::Length() const {
    return std::sqrt(LengthSquared());
}

float Vector2::LengthSquared() const {
    return x * x + y * y;
}

Vector2 Vector2::Normalized() const {
    float len = Length();
    if (len > 0.0f) {
        return *this / len;
    }
    return Zero;
}

void Vector2::Normalize() {
    float len = Length();
    if (len > 0.0f) {
        *this /= len;
    }
}

const Vector2 Vector2::Zero(0.0f, 0.0f);
const Vector2 Vector2::One(1.0f, 1.0f);
const Vector2 Vector2::UnitX(1.0f, 0.0f);
const Vector2 Vector2::UnitY(0.0f, 1.0f);

Vector2 operator*(float scalar, const Vector2& vector) {
    return vector * scalar;
}

}
