#include <iostream>
#include "../include/Rendering/IRenderer.h"
#include "../include/Rendering/NullRenderer.h"
#include "../include/Geometry/Mesh.h"  

using namespace Rendering;
using namespace Geometry;

void TestRendererInterface() {
    std::cout << "Testing Renderer Interface..." << std::endl;
    
    NullRenderer renderer;
    if (renderer.Initialize(800, 600, "TestRendererInterface")) {
        std::cout << "NullRenderer initialization test passed" << std::endl;
    } else {
        std::cout << "NullRenderer initialization test failed" << std::endl;
    }
    
    renderer.SetViewport(0, 0, 800, 600);
    renderer.SetProjectionMatrix(Math3D::Matrix4::Identity());
    
    if (renderer.GetWidth() == 800 && renderer.GetHeight() == 600) {
        std::cout << "Renderer dimensions test passed" << std::endl;
    } else {
        std::cout << "Renderer dimensions test failed" << std::endl;
    }
    
    renderer.EnableState(RenderState::DepthTest);
    renderer.DisableState(RenderState::Blending);
    
    std::cout << "Render state interface test passed" << std::endl;
    
    renderer.BeginFrame();
    renderer.Clear(ClearFlags::Color | ClearFlags::Depth, Color::Blue());
    renderer.EndFrame();
    
    std::cout << "Frame control test passed" << std::endl;
    
    Mesh cube = Mesh::CreateCube();
    renderer.DrawMesh(cube, Math3D::Matrix4::Identity());
    renderer.DrawMesh(cube);
    
    std::cout << "DrawMesh interface test passed" << std::endl;
    
    std::cout << "Renderer name: " << renderer.GetName() << std::endl;
    
    IRenderer* rendererPtr = &renderer;
    if (rendererPtr->GetName() == std::string("NullRenderer")) {
        std::cout << "Polymorphic interface test passed" << std::endl;
    } else {
        std::cout << "Polymorphic interface test failed" << std::endl;
    }
}

int main() {
    TestRendererInterface();
    return 0;
}
