#include "Core/GraphicsEngine.h"

namespace Core {

GraphicsEngine::GraphicsEngine() = default;

GraphicsEngine::~GraphicsEngine() {
    Shutdown();
}

bool GraphicsEngine::Initialize(int width, int height, const char* title) {
    m_renderer = std::make_unique<Rendering::OpenGLRenderer>();
    return m_renderer->Initialize(width, height, title);
}

void GraphicsEngine::Shutdown() {
    if (m_renderer) {
        m_renderer->Shutdown();
        m_renderer.reset();
    }
}

void GraphicsEngine::BeginFrame() {
    m_renderer->BeginFrame();
}

void GraphicsEngine::EndFrame() {
    m_renderer->EndFrame();
}

void GraphicsEngine::Clear(const Rendering::Color& color) {
    m_renderer->Clear(Rendering::ClearFlags::Color | Rendering::ClearFlags::Depth, color);
}

void GraphicsEngine::DrawMesh(const Geometry::Mesh& mesh, const Math3D::Matrix4& transform) {
    m_renderer->DrawMesh(mesh, transform);
}

void GraphicsEngine::DrawMesh(const Geometry::Mesh& mesh) {
    m_renderer->DrawMesh(mesh);
}

bool GraphicsEngine::ShouldClose() const {
    return m_renderer ? m_renderer->ShouldClose() : true;
}

} 
