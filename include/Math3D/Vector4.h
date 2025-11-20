#pragma once

namespace Math3D {
    class Vector3;
}

namespace Math3D {

class Vector4 {
public:
    float x, y, z, w;

    Vector4();
    Vector4(float x, float y, float z, float w);
    Vector4(const Vector3& xyz, float w);  
    Vector4(const Vector4& other) = default;

    Vector4& operator=(const Vector4& other) = default;

    Vector4 operator+(const Vector4& other) const;
    Vector4 operator-(const Vector4& other) const;
    Vector4 operator*(float scalar) const;
    Vector4 operator/(float scalar) const;

    Vector4& operator+=(const Vector4& other);
    Vector4& operator-=(const Vector4& other);
    Vector4& operator*=(float scalar);
    Vector4& operator/=(float scalar);

    bool operator==(const Vector4& other) const;
    bool operator!=(const Vector4& other) const;

    float Dot(const Vector4& other) const;
    float Length() const;
    float LengthSquared() const;
    Vector4 Normalized() const;
    void Normalize();
    
    Vector3 XYZ() const;
    
    static const Vector4 Zero;
    static const Vector4 One;
};

Vector4 operator*(float scalar, const Vector4& vector);

} 
