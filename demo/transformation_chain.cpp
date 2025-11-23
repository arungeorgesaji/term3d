#include <iostream>
#include <chrono>
#include <cmath>
#include "../include/Core/GraphicsEngine.h"
#include "../include/Geometry/Mesh.h"
#include "../include/Math3D/MathUtils.h"

using namespace Core;
using namespace Geometry;
using namespace Math3D;
using Rendering::Color;

int main() {
    std::cout << "=== Term3D - Transformation Chain Demo ===" << std::endl;
    
    GraphicsEngine engine;
    if (!engine.Initialize(800, 600, "Term3D - Transformation Chain")) {
        return -1;
    }
    
    Mesh cube = Mesh::CreateCube(0.5f);
    
    auto startTime = std::chrono::high_resolution_clock::now();
    
    while (!engine.ShouldClose()) {
        float time = std::chrono::duration<float>(
            std::chrono::high_resolution_clock::now() - startTime).count();
        
        engine.BeginFrame();
        engine.Clear(Color(0.15f, 0.1f, 0.1f, 1.0f));
        
        Matrix4 baseTransform = Matrix4::Identity();
        
        for (int i = 0; i < 5; i++) {
            float segmentTime = time * (0.8f + i * 0.2f);
            
            Matrix4 translation = Matrix4::Translation(Vector3(1.2f, 0.0f, 0.0f));
            Matrix4 rotation = Matrix4::RotationY(segmentTime) * 
                              Matrix4::RotationZ(std::sin(segmentTime + i) * 0.5f);
            Matrix4 scale = Matrix4::Scaling(Vector3(0.8f, 0.8f, 0.8f));
            
            baseTransform = baseTransform * translation * rotation * scale;
            engine.DrawMesh(cube, baseTransform);
        }
        
        engine.EndFrame();
        
        if (time > 12.0f) break;
    }
    
    engine.Shutdown();
    std::cout << "Transformation chain demo completed!" << std::endl;
    return 0;
}
