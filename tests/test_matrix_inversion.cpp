#include <iostream>
#include <chrono>
#include "../include/Math3D/Matrix4.h"
#include "../include/Math3D/MathUtils.h"

using namespace Math3D;
using namespace std::chrono;

void TestInversion() {
    std::cout << "Testing Matrix Inversion..." << std::endl;
    
    Matrix4 affine = Matrix4::Translation(Vector3(1, 2, 3)) * 
                    Matrix4::RotationY(MathUtils::Radians(45)) * 
                    Matrix4::Scaling(Vector3(2, 2, 2));
    
    const int iterations = 100000;
    
    auto start = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        Matrix4 inv = affine.FastInvertAffine();
    }
    auto end = high_resolution_clock::now();
    auto optimizedTime = duration_cast<microseconds>(end - start);
    
    start = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        Matrix4 inv = affine.Inverted(); 
    }
    auto end2 = high_resolution_clock::now();
    auto fullTime = duration_cast<microseconds>(end2 - start);
    
    std::cout << "Optimized affine inversion: " << optimizedTime.count() << " μs" << std::endl;
    std::cout << "Full inversion (with check): " << fullTime.count() << " μs" << std::endl;
    std::cout << "Performance ratio: " << (float)fullTime.count() / optimizedTime.count() << "x" << std::endl;
}

int main() {
    TestInversion();
    return 0;
}
