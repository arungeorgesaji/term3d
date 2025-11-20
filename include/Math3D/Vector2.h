#pragma once

namespace Math3D {

class Vector2 {
public:
    float x, y;

    Vector2();
    Vector2(float x, float y);
    Vector2(const Vector2& other) = default;

    Vector2& operator=(const Vector2& other) = default;

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;

    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(float scalar);
    Vector2& operator/=(float scalar);

    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;

    float Dot(const Vector2& other) const;
    float Length() const;
    float LengthSquared() const;
    Vector2 Normalized() const;
    void Normalize();
    
    static const Vector2 Zero;
    static const Vector2 One;
    static const Vector2 UnitX;
    static const Vector2 UnitY;
};

Vector2 operator*(float scalar, const Vector2& vector);

} 
