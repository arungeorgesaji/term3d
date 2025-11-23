#include <iostream>
#include <chrono>
#include "../include/Core/GraphicsEngine.h"
#include "../include/Core/Input.h"
#include "../include/Core/KeyCodes.h"
#include "../include/Geometry/Mesh.h"
#include "../include/Math3D/MathUtils.h"

using namespace Core;
using namespace Geometry;
using namespace Math3D;
using Rendering::Color;

int main() {
    std::cout << "=== Term3D - Interactive Cube ===" << std::endl;
    std::cout << "Controls: WASD to rotate, SPACE to reset, ESC to quit" << std::endl;
    
    GraphicsEngine engine;
    if (!engine.Initialize(800, 600, "Term3D - Interactive")) {
        return -1;
    }
    
    Mesh cube = Mesh::CreateCube(1.5f);
    
    float rotationX = 0.0f;
    float rotationY = 0.0f;
    bool autoRotate = false; 
    
    auto startTime = std::chrono::high_resolution_clock::now();
    
    while (!engine.ShouldClose()) {
        float time = std::chrono::duration<float>(
            std::chrono::high_resolution_clock::now() - startTime).count();
        
        if (Input::IsKeyPressed(Key::ESCAPE)) {
            break;
        }
        
        if (Input::IsKeyPressed(Key::SPACE)) {
            rotationX = rotationY = 0.0f;
            autoRotate = true;
        }
        
        if (Input::IsKeyPressed(Key::W)) {
            rotationX += 0.05f;
            autoRotate = false;
        }

        if (Input::IsKeyPressed(Key::S)) {
            rotationX -= 0.05f;
            autoRotate = false;
        }
        if (Input::IsKeyPressed(Key::A)) {
            rotationY += 0.05f;
            autoRotate = false;
        }
        if (Input::IsKeyPressed(Key::D)) {
            rotationY -= 0.05f;
            autoRotate = false;
        }
        
        if (autoRotate) {
            rotationY = time * 1.0f;
            rotationX = time * 0.7f;
        }
        
        Matrix4 model = Matrix4::RotationY(rotationY) * Matrix4::RotationX(rotationX);
        
        engine.BeginFrame();
        engine.Clear(Color(0.1f, 0.15f, 0.3f, 1.0f));
        engine.DrawMesh(cube, model);
        engine.EndFrame();
        
        static bool printed = false;
        if (!printed && time > 2.0f) {
            std::cout << "Input system working! Try WASD keys." << std::endl;
            printed = true;
        }
    }
    
    engine.Shutdown();
    std::cout << "Interactive demo completed!" << std::endl;
    return 0;
}
