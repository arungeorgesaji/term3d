#include <iostream>
#include "../include/Math3D/Matrix4.h"
#include "../include/Math3D/MathUtils.h"

using namespace Math3D;

void TestMatrixInversion() {
    std::cout << "Testing Matrix4 Inversion..." << std::endl;
    
    Matrix4 identity = Matrix4::Identity();
    Matrix4 identityInv = identity.Inverted();
    
    if (identity == identityInv) {
        std::cout << "Identity inversion test passed" << std::endl;
    } else {
        std::cout << "Identity inversion test failed" << std::endl;
    }
    
    Vector3 translation(2.0f, 3.0f, 4.0f);
    Matrix4 translationMat = Matrix4::Translation(translation);
    Matrix4 translationInv = translationMat.Inverted();
    
    Matrix4 expectedTranslationInv = Matrix4::Translation(Vector3(-2.0f, -3.0f, -4.0f));
    
    if (translationInv == expectedTranslationInv) {
        std::cout << "Translation inversion test passed" << std::endl;
    } else {
        std::cout << "Translation inversion test failed" << std::endl;
        std::cout << "Expected: " << expectedTranslationInv(0, 3) << "," 
                  << expectedTranslationInv(1, 3) << "," << expectedTranslationInv(2, 3) << std::endl;
        std::cout << "Got: " << translationInv(0, 3) << "," 
                  << translationInv(1, 3) << "," << translationInv(2, 3) << std::endl;
    }
    
    Vector3 scale(2.0f, 3.0f, 4.0f);
    Matrix4 scalingMat = Matrix4::Scaling(scale);
    Matrix4 scalingInv = scalingMat.Inverted();
    
    Matrix4 expectedScalingInv = Matrix4::Scaling(Vector3(0.5f, 1.0f/3.0f, 0.25f));
    
    if (scalingInv == expectedScalingInv) {
        std::cout << "Scaling inversion test passed" << std::endl;
    } else {
        std::cout << "Scaling inversion test failed" << std::endl;
    }
    
    Matrix4 transform = Matrix4::Translation(Vector3(1.0f, 2.0f, 3.0f)) * 
                       Matrix4::RotationY(MathUtils::Radians(45.0f)) * 
                       Matrix4::Scaling(Vector3(2.0f, 2.0f, 2.0f));
    
    Matrix4 transformInv = transform.Inverted();
    Matrix4 shouldBeIdentity = transform * transformInv;
    
    bool isIdentity = true;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            float expected = (row == col) ? 1.0f : 0.0f;
            if (!MathUtils::Approximately(shouldBeIdentity(row, col), expected, 1e-4f)) {
                isIdentity = false;
                break;
            }
        }
        if (!isIdentity) break;
    }
    
    if (isIdentity) {
        std::cout << "Combined transformation inversion test passed" << std::endl;
    } else {
        std::cout << "Combined transformation inversion test failed" << std::endl;
    }
    
    Matrix4 simpleMat = Matrix4::Scaling(Vector3(2.0f, 3.0f, 4.0f));
    float det = simpleMat.Determinant();
    float expectedDet = 2.0f * 3.0f * 4.0f; 
    
    if (MathUtils::Approximately(det, expectedDet)) {
        std::cout << "Determinant calculation test passed" << std::endl;
    } else {
        std::cout << "Determinant calculation test failed: " << det << " vs " << expectedDet << std::endl;
    }
}

int main() {
    TestMatrixInversion();
    return 0;
}
