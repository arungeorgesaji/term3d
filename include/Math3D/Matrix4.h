#pragma once

#include "Math3D/Vector3.h"
#include "Math3D/Vector4.h"

namespace Math3D {

class Matrix4 {
private:
    float m[16]; 

public:
    Matrix4();
    Matrix4(const Matrix4& other) = default;
    explicit Matrix4(const float data[16]);
    
    Matrix4& operator=(const Matrix4& other) = default;
    
    float& operator()(int row, int col);
    float operator()(int row, int col) const;
    const float* Data() const { return m; }
    
    Matrix4 operator+(const Matrix4& other) const;
    Matrix4 operator-(const Matrix4& other) const;
    Matrix4 operator*(const Matrix4& other) const;
    Vector4 operator*(const Vector4& vector) const;
    Matrix4 operator*(float scalar) const;
    
    Matrix4& operator+=(const Matrix4& other);
    Matrix4& operator-=(const Matrix4& other);
    Matrix4& operator*=(const Matrix4& other);
    Matrix4& operator*=(float scalar);
    
    bool operator==(const Matrix4& other) const;
    bool operator!=(const Matrix4& other) const;
    
    Matrix4 Transposed() const;
    float Determinant() const;
    bool IsAffine() const;
    Matrix4 FastInvertAffine() const;
    Matrix4 Inverted() const;
    
    static Matrix4 Identity();
    static Matrix4 Translation(const Vector3& translation);
    static Matrix4 Scaling(const Vector3& scale);
    static Matrix4 RotationX(float angle);
    static Matrix4 RotationY(float angle);
    static Matrix4 RotationZ(float angle);
    
    static Matrix4 Perspective(float fov, float aspect, float near, float far);
    static Matrix4 Orthographic(float left, float right, float bottom, float top, float near, float far);
    
    static Matrix4 LookAt(const Vector3& eye, const Vector3& target, const Vector3& up);
};

Matrix4 operator*(float scalar, const Matrix4& matrix);

} 
