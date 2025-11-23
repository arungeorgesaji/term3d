#include <iostream>
#include <chrono>
#include "../include/Rendering/OpenGLRenderer.h"
#include "../include/Geometry/Mesh.h"
#include "../include/Math3D/MathUtils.h"

using namespace Rendering;
using namespace Geometry;
using namespace Math3D;

int main() {
    std::cout << "Term3D - Simple Cube Demo" << std::endl;
    
    OpenGLRenderer renderer;
    if (!renderer.Initialize(800, 600)) {
        std::cerr << "Failed to initialize renderer!" << std::endl;
        return -1;
    }
    
    Mesh cube = Mesh::CreateCube(1.0f);
    
    Matrix4 projection = Matrix4::Perspective(
        MathUtils::Radians(45.0f), 
        800.0f / 600.0f, 
        0.1f, 
        100.0f
    );
    
    Matrix4 view = Matrix4::LookAt(
        Vector3(0.0f, 0.0f, 5.0f),  
        Vector3(0.0f, 0.0f, 0.0f),  
        Vector3(0.0f, 1.0f, 0.0f)   
    );
    
    renderer.SetProjectionMatrix(projection);
    renderer.SetViewMatrix(view);
    renderer.EnableState(RenderState::DepthTest);
    
    auto startTime = std::chrono::high_resolution_clock::now();
    
    while (!renderer.ShouldClose()) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float>(currentTime - startTime).count();
        
        Matrix4 model = Matrix4::RotationY(time) * Matrix4::RotationX(time * 0.5f);
        
        renderer.BeginFrame();
        renderer.Clear(ClearFlags::Color | ClearFlags::Depth, Color(0.1f, 0.1f, 0.1f, 1.0f));
        
        renderer.DrawMesh(cube, model);
        
        renderer.EndFrame();
    }
    
    renderer.Shutdown();
    std::cout << "Demo finished successfully!" << std::endl;
    return 0;
}
