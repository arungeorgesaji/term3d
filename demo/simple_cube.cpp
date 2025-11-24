#include <iostream>
#include <chrono>
#include "Core/GraphicsEngine.h"
#include "Geometry/Mesh.h"
#include "Math3D/MathUtils.h"

using namespace Core;
using namespace Geometry;
using namespace Math3D;
using Rendering::Color;

int main() {
    std::cout << "=== Term3D WORKING DEMO ===" << std::endl;
    std::cout << "Showing rotating 3D cube with simple transformations" << std::endl;
    
    GraphicsEngine engine;
    if (!engine.Initialize(800, 600, "Term3D - Working Cube")) {
        std::cerr << "Failed to initialize graphics engine!" << std::endl;
        return -1;
    }
    
    Mesh cube = Mesh::CreateCube(1.5f);
    std::cout << "Cube created: " << cube.GetTriangleCount() << " triangles" << std::endl;
    
    auto startTime = std::chrono::high_resolution_clock::now();
    int frameCount = 0;
    
    std::cout << "Starting animation loop..." << std::endl;
    
    while (!engine.ShouldClose()) {
        frameCount++;
        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float>(currentTime - startTime).count();
        
        Matrix4 rotationY = Matrix4::RotationY(time * 1.0f);
        Matrix4 rotationX = Matrix4::RotationX(time * 0.7f);  
        Matrix4 model = rotationY * rotationX;
        
        Matrix4 scale = Matrix4::Scaling(Vector3(1.0f, 1.0f, 1.0f));
        model = model * scale;
        
        engine.BeginFrame();
        engine.Clear(Color(0.1f, 0.15f, 0.3f, 1.0f));  
        engine.DrawMesh(cube, model);
        engine.EndFrame();
        
        if (frameCount % 120 == 0) {
            float fps = frameCount / time;
            std::cout << "Frame " << frameCount << " - FPS: " << fps << " - Time: " << time << "s" << std::endl;
        }
        
        if (time > 10.0f) {
            break;
        }
    }
    
    engine.Shutdown();
    std::cout << "Demo completed successfully!" << std::endl;
    std::cout << "Total frames: " << frameCount << std::endl;
    std::cout << "=== DEMO FINISHED ===" << std::endl;
    return 0;
}
