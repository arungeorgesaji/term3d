#include <iostream>
#include "../include/Math3D/Matrix4.h"
#include "../include/Math3D/MathUtils.h"

using namespace Math3D;

void TestMatrix4() {
    std::cout << "Testing Matrix4..." << std::endl;
    
    Matrix4 identity = Matrix4::Identity();
    if (identity(0, 0) == 1.0f && identity(1, 1) == 1.0f && 
        identity(2, 2) == 1.0f && identity(3, 3) == 1.0f) {
        std::cout << "Identity matrix test passed" << std::endl;
    } else {
        std::cout << "Identity matrix test failed" << std::endl;
    }
    
    Vector3 translation(2.0f, 3.0f, 4.0f);
    Matrix4 translationMat = Matrix4::Translation(translation);
    
    if (translationMat(0, 3) == 2.0f && translationMat(1, 3) == 3.0f && translationMat(2, 3) == 4.0f) {
        std::cout << "Translation matrix test passed" << std::endl;
    } else {
        std::cout << "Translation matrix test failed" << std::endl;
    }
    
    Matrix4 a = Matrix4::Identity();
    Matrix4 b = Matrix4::Identity();
    Matrix4 result = a * b;
    
    if (result == Matrix4::Identity()) {
        std::cout << "Matrix multiplication test passed" << std::endl;
    } else {
        std::cout << "Matrix multiplication test failed" << std::endl;
    }
    
    Vector4 vec(1.0f, 2.0f, 3.0f, 1.0f);
    Vector4 transformed = translationMat * vec;
    
    if (transformed.x == 3.0f && transformed.y == 5.0f && transformed.z == 7.0f) {
        std::cout << "Vector transformation test passed" << std::endl;
    } else {
        std::cout << "Vector transformation test failed" << std::endl;
    }
}

int main() {
    TestMatrix4();
    return 0;
}
