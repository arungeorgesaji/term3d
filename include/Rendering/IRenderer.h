#pragma once
#include "Rendering/Types.h"
#include "Math3D/Matrix4.h"
#include <memory>

namespace Geometry {
    class Mesh;  
}

namespace Rendering {

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual bool Initialize(int width, int height, const char* title) = 0;
    virtual void Shutdown() = 0;
    virtual void Resize(int width, int height) = 0;

    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    virtual void Clear(ClearFlags flags, const Color& color = Color::Black()) = 0;

    virtual void SetRenderState(RenderState state) = 0;
    virtual void EnableState(RenderState state) = 0;
    virtual void DisableState(RenderState state) = 0;

    virtual void SetViewport(int x, int y, int width, int height) = 0;
    virtual void SetProjectionMatrix(const Math3D::Matrix4& projection) = 0;
    virtual void SetViewMatrix(const Math3D::Matrix4& view) = 0;

    virtual void DrawMesh(const Geometry::Mesh& mesh, const Math3D::Matrix4& transform) = 0;
    virtual void DrawMesh(const Geometry::Mesh& mesh) = 0;

    virtual const char* GetName() const = 0;
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;

    virtual int GetDrawCallCount() const { return 0; }
    virtual int GetTriangleCount() const { return 0; }
    virtual void ResetStatistics() {}
};

} 
