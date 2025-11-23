#pragma once
#include "Rendering/IRenderer.h"
#include "Geometry/Mesh.h"
#include "Math3D/Matrix4.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

namespace Rendering {

class OpenGLRenderer : public IRenderer {
private:
    GLFWwindow* m_window;
    int m_width, m_height;
    
    Math3D::Matrix4 m_projection;
    Math3D::Matrix4 m_view;
    
    RenderState m_currentState;
    
    struct MeshResources {
        GLuint vao;
        GLuint vbo;
        GLuint ebo;
        size_t indexCount;
    };
    
    std::unordered_map<const Geometry::Mesh*, MeshResources> m_meshResources;
    
    GLuint m_shaderProgram;
    
public:
    OpenGLRenderer();
    ~OpenGLRenderer();
    
    bool Initialize(int width, int height) override;
    void Shutdown() override;
    void Resize(int width, int height) override;
    
    void BeginFrame() override;
    void EndFrame() override;
    void Clear(ClearFlags flags, const Color& color = Color::Black()) override;
    
    void SetRenderState(RenderState state) override;
    void EnableState(RenderState state) override;
    void DisableState(RenderState state) override;
    
    void SetViewport(int x, int y, int width, int height) override;
    void SetProjectionMatrix(const Math3D::Matrix4& projection) override;
    void SetViewMatrix(const Math3D::Matrix4& view) override;
    
    void DrawMesh(const Geometry::Mesh& mesh, const Math3D::Matrix4& transform) override;
    void DrawMesh(const Geometry::Mesh& mesh) override;
    
    const char* GetName() const override { return "OpenGLRenderer"; }
    int GetWidth() const override { return m_width; }
    int GetHeight() const override { return m_height; }
    
    GLFWwindow* GetWindow() const { return m_window; }
    bool ShouldClose() const;

private:
    bool InitializeGLFW();
    bool InitializeGLEW();
    bool InitializeShaders();
    void InitializeMesh(const Geometry::Mesh& mesh);
    void CleanupMesh(const Geometry::Mesh& mesh);
    
    GLuint CompileShader(const char* source, GLenum type);
    GLuint CreateShaderProgram(const char* vertexSrc, const char* fragmentSrc);
    
    void ApplyRenderState(RenderState newState);
};

} 
