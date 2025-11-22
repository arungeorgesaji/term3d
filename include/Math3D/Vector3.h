#pragma once

namespace Math3D {

class Vector3 {
public:
    float x, y, z;

    Vector3();
    Vector3(float x, float y, float z);
    Vector3(const Vector3& other) = default;

    Vector3& operator=(const Vector3& other) = default;

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator-() const;
    Vector3 operator*(float scalar) const;
    Vector3 operator/(float scalar) const;

    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
    Vector3& operator*=(float scalar);
    Vector3& operator/=(float scalar);

    bool operator==(const Vector3& other) const;
    bool operator!=(const Vector3& other) const;

    float Dot(const Vector3& other) const;
    Vector3 Cross(const Vector3& other) const;
    float Length() const;
    float LengthSquared() const;
    Vector3 Normalized() const;
    void Normalize();
    
    static const Vector3 Zero;
    static const Vector3 One;
    static const Vector3 UnitX;
    static const Vector3 UnitY;
    static const Vector3 UnitZ;
};

Vector3 operator*(float scalar, const Vector3& vector);

} 
