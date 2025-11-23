#pragma once
#include "Geometry/Vertex.h"
#include "Geometry/BoundingBox.h"
#include <vector>
#include <cstdint>
#include <memory>

namespace Geometry {

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    BoundingBox bounds;
    
    Mesh() = default;
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
    
    void CalculateNormals();
    void CalculateTangents();
    void UpdateBounds();
    void Clear();
    bool IsValid() const;
    
    static Mesh CreateCube(float size = 1.0f);
    static Mesh CreatePlane(float size = 1.0f, uint32_t segments = 1);
    static Mesh CreateSphere(float radius = 1.0f, uint32_t segments = 16);
    static Mesh CreateCylinder(float radius = 0.5f, float height = 1.0f, uint32_t segments = 16);
    
    size_t GetVertexCount() const { return vertices.size(); }
    size_t GetIndexCount() const { return indices.size(); }
    size_t GetTriangleCount() const { return indices.size() / 3; }
    
    void Transform(const Math3D::Matrix4& transform);
};

} 
