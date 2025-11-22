#pragma once
#include "Math3D/Vector3.h"

namespace Math3D {

class Matrix3 {
private:
    float m[9]; 

public:
    Matrix3();
    explicit Matrix3(const float data[9]);
    
    float& operator()(int row, int col);
    float operator()(int row, int col) const;
    
    Matrix3 Transposed() const;
    Matrix3 operator*(const Matrix3& other) const;
    Vector3 operator*(const Vector3& vector) const;
    
    static Matrix3 Identity();
};

} 
