#pragma once
#include "Rendering/OpenGLRenderer.h"
#include "Geometry/Mesh.h"
#include "Math3D/Matrix4.h"
#include <memory>

namespace Core {

class GraphicsEngine {
private:
    std::unique_ptr<Rendering::OpenGLRenderer> m_renderer;

public:
    GraphicsEngine();
    ~GraphicsEngine();
    
    bool Initialize(int width, int height, const char* title = "Term3D");
    void Shutdown();
    
    void BeginFrame();
    void EndFrame();
    void Clear(const Rendering::Color& color = Rendering::Color::Black());
    
    void DrawMesh(const Geometry::Mesh& mesh, const Math3D::Matrix4& transform);
    void DrawMesh(const Geometry::Mesh& mesh);
    
    bool ShouldClose() const;
};

}
