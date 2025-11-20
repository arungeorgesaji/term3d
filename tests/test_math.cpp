#include <iostream>
#include "Math3D/Vector3.h"
#include "Math3D/MathUtils.h"

using namespace Math3D;

void TestVector3() {
    std::cout << "Testing Vector3..." << std::endl;
    
    Vector3 v1(1.0f, 2.0f, 3.0f);
    Vector3 v2(4.0f, 5.0f, 6.0f);
    
    Vector3 sum = v1 + v2;
    Vector3 expectedSum(5.0f, 7.0f, 9.0f);
    
    if (sum == expectedSum) {
        std::cout << "Addition test passed" << std::endl;
    } else {
        std::cout << "Addition test failed" << std::endl;
    }
    
    float dot = v1.Dot(v2);
    float expectedDot = 32.0f; 
    
    if (MathUtils::Approximately(dot, expectedDot)) {
        std::cout << "Dot product test passed" << std::endl;
    } else {
        std::cout << "Dot product test failed: " << dot << " vs " << expectedDot << std::endl;
    }
    
    Vector3 cross = v1.Cross(v2);
    Vector3 expectedCross(-3.0f, 6.0f, -3.0f); 
    
    if (cross == expectedCross) {
        std::cout << "Cross product test passed" << std::endl;
    } else {
        std::cout << "Cross product test failed" << std::endl;
    }
    
    Vector3 v3(3.0f, 0.0f, 0.0f);
    Vector3 normalized = v3.Normalized();
    
    if (MathUtils::Approximately(normalized.Length(), 1.0f)) {
        std::cout << "Normalization test passed" << std::endl;
    } else {
        std::cout << "Normalization test failed" << std::endl;
    }
}

int main() {
    TestVector3();
    return 0;
}
