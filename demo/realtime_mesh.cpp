#include <iostream>
#include <chrono>
#include <cmath>
#include "../include/Core/GraphicsEngine.h"
#include "../include/Geometry/Mesh.h"
#include <cmath>
#include "../include/Math3D/MathUtils.h"

using namespace Core;
using namespace Geometry;
using namespace Math3D;
using Rendering::Color;

Mesh CreatePulsingSphere(float time, float baseRadius = 0.7f) {
    float pulse = std::sin(time * 2.0f) * 0.2f + 1.0f;
    return Mesh::CreateSphere(baseRadius * pulse, 12);
}

int main() {
    std::cout << "=== Term3D - Real-time Mesh Generation ===" << std::endl;
    
    GraphicsEngine engine;
    if (!engine.Initialize(800, 600, "Term3D - Real-time Meshes")) {
        return -1;
    }
    
    auto startTime = std::chrono::high_resolution_clock::now();
    
    while (!engine.ShouldClose()) {
        float time = std::chrono::duration<float>(
            std::chrono::high_resolution_clock::now() - startTime).count();
        
        engine.BeginFrame();
        engine.Clear(Color(0.08f, 0.12f, 0.1f, 1.0f));
        
        Mesh pulsingSphere = CreatePulsingSphere(time);
        
        uint32_t segments = 8 + (int)(std::sin(time) * 2 + 2);
        Mesh morphingPlane = Mesh::CreatePlane(1.5f, segments);
        
        Matrix4 sphereTransform = Matrix4::RotationY(time * 0.7f) * 
                                 Matrix4::Translation(Vector3(-1.5f, 0.0f, 0.0f));
        Matrix4 planeTransform = Matrix4::RotationX(time * 0.5f) * 
                                Matrix4::Translation(Vector3(1.5f, 0.0f, 0.0f));
        
        engine.DrawMesh(pulsingSphere, sphereTransform);
        engine.DrawMesh(morphingPlane, planeTransform);
        
        engine.EndFrame();
        
        if (time > 15.0f) break;
    }
    
    engine.Shutdown();
    std::cout << "Real-time mesh demo completed!" << std::endl;
    return 0;
}
