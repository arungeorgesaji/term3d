#pragma once
#include "Rendering/IRenderer.h"
#include "Math3D/Matrix4.h"
#include "Geometry/Mesh.h"

namespace Rendering {

class NullRenderer : public IRenderer {
private:
    int m_width = 0;
    int m_height = 0;
    Math3D::Matrix4 m_projection;
    Math3D::Matrix4 m_view;

public:
    bool Initialize(int width, int height, const char* title) override {
        m_width = width;
        m_height = height;
        return true;
    }
    
    void Shutdown() override {}
    
    void Resize(int width, int height) override {
        m_width = width;
        m_height = height;
    }
    
    void BeginFrame() override {}
    void EndFrame() override {}
    
    void Clear(ClearFlags flags, const Color& color = Color::Black()) override {}
    
    void SetRenderState(RenderState state) override {}
    void EnableState(RenderState state) override {}
    void DisableState(RenderState state) override {}
    
    void SetViewport(int x, int y, int width, int height) override {}
    
    void SetProjectionMatrix(const Math3D::Matrix4& projection) override {
        m_projection = projection;
    }
    
    void SetViewMatrix(const Math3D::Matrix4& view) override {
        m_view = view;
    }

    void DrawMesh(const Geometry::Mesh& mesh, const Math3D::Matrix4& transform) override {}
    void DrawMesh(const Geometry::Mesh& mesh) override {}
    
    const char* GetName() const override { return "NullRenderer"; }
    int GetWidth() const override { return m_width; }
    int GetHeight() const override { return m_height; }
};

}
