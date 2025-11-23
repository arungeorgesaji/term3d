#include "Geometry/Mesh.h"
#include "Math3D/MathUtils.h"
#include <cmath>
#include <cstring>

namespace Geometry {

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
    : vertices(vertices), indices(indices) {
    UpdateBounds();
}

void Mesh::CalculateNormals() {
    for (auto& vertex : vertices) {
        vertex.normal = Math3D::Vector3::Zero;
    }
    
    for (size_t i = 0; i < indices.size(); i += 3) {
        uint32_t i0 = indices[i];
        uint32_t i1 = indices[i + 1];
        uint32_t i2 = indices[i + 2];

        if (i0 >= vertices.size() || i1 >= vertices.size() || i2 >= vertices.size()) {
            continue; 
        }
        
        const Math3D::Vector3& v0 = vertices[i0].position;
        const Math3D::Vector3& v1 = vertices[i1].position;
        const Math3D::Vector3& v2 = vertices[i2].position;
        
        Math3D::Vector3 edge1 = v1 - v0;
        Math3D::Vector3 edge2 = v2 - v0;
        Math3D::Vector3 normal = edge1.Cross(edge2);
        
        vertices[i0].normal += normal;
        vertices[i1].normal += normal;
        vertices[i2].normal += normal;
    }
    
    for (auto& vertex : vertices) {
        vertex.normal.Normalize();
    }
}

void Mesh::CalculateTangents() {
    for (auto& vertex : vertices) {
        vertex.tangent = Math3D::Vector3::Zero;
        vertex.bitangent = Math3D::Vector3::Zero;
    }
    
    for (size_t i = 0; i < indices.size(); i += 3) {
        uint32_t i0 = indices[i];
        uint32_t i1 = indices[i + 1];
        uint32_t i2 = indices[i + 2];
        
        Vertex& v0 = vertices[i0];
        Vertex& v1 = vertices[i1];
        Vertex& v2 = vertices[i2];
        
        Math3D::Vector3 edge1 = v1.position - v0.position;
        Math3D::Vector3 edge2 = v2.position - v0.position;
        
        Math3D::Vector2 deltaUV1 = v1.texCoord - v0.texCoord;
        Math3D::Vector2 deltaUV2 = v2.texCoord - v0.texCoord;
        
        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
        
        Math3D::Vector3 tangent, bitangent;
        
        tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
        tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
        tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
        tangent.Normalize();
        
        bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
        bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
        bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
        bitangent.Normalize();
        
        v0.tangent += tangent;
        v1.tangent += tangent;
        v2.tangent += tangent;
        
        v0.bitangent += bitangent;
        v1.bitangent += bitangent;
        v2.bitangent += bitangent;
    }
    
    for (auto& vertex : vertices) {
        vertex.tangent = (vertex.tangent - vertex.normal * vertex.normal.Dot(vertex.tangent)).Normalized();
        vertex.bitangent.Normalize();
        
        vertex.bitangent = vertex.normal.Cross(vertex.tangent).Normalized();
    }
}

void Mesh::UpdateBounds() {
    bounds.Reset();
    for (const auto& vertex : vertices) {
        bounds.Expand(vertex.position);
    }
}

void Mesh::Clear() {
    vertices.clear();
    indices.clear();
    bounds.Reset();
}

bool Mesh::IsValid() const {
    return !vertices.empty() && 
           (indices.empty() || (indices.size() % 3 == 0));
}


Math3D::Matrix3 ExtractRotationMatrix(const Math3D::Matrix4& transform) {
    Math3D::Matrix3 rotation;
    rotation(0, 0) = transform(0, 0); rotation(0, 1) = transform(0, 1); rotation(0, 2) = transform(0, 2);
    rotation(1, 0) = transform(1, 0); rotation(1, 1) = transform(1, 1); rotation(1, 2) = transform(1, 2);
    rotation(2, 0) = transform(2, 0); rotation(2, 1) = transform(2, 1); rotation(2, 2) = transform(2, 2);
    return rotation;
}

void Mesh::Transform(const Math3D::Matrix4& transform) {
    Math3D::Matrix3 normalMatrix = ExtractRotationMatrix(transform).Transposed();
    
    for (auto& vertex : vertices) {
        Math3D::Vector4 pos(vertex.position, 1.0f);
        pos = transform * pos;
        vertex.position = pos.XYZ();
        
        vertex.normal = (normalMatrix * vertex.normal).Normalized();
        vertex.tangent = (normalMatrix * vertex.tangent).Normalized();
        vertex.bitangent = (normalMatrix * vertex.bitangent).Normalized();
    }
    
    UpdateBounds();
}

Mesh Mesh::CreateCube(float size) {
    Mesh mesh;
    float halfSize = size * 0.5f;
    
    mesh.vertices.push_back(Vertex(Math3D::Vector3(-halfSize, -halfSize,  halfSize), Math3D::Vector3(0,0,1), Math3D::Vector3(1,0,0), Math3D::Vector3(0,1,0), Math3D::Vector2(0,0)));
    mesh.vertices.push_back(Vertex(Math3D::Vector3( halfSize, -halfSize,  halfSize), Math3D::Vector3(0,0,1), Math3D::Vector3(1,0,0), Math3D::Vector3(0,1,0), Math3D::Vector2(1,0)));
    mesh.vertices.push_back(Vertex(Math3D::Vector3( halfSize,  halfSize,  halfSize), Math3D::Vector3(0,0,1), Math3D::Vector3(1,0,0), Math3D::Vector3(0,1,0), Math3D::Vector2(1,1)));
    mesh.vertices.push_back(Vertex(Math3D::Vector3(-halfSize,  halfSize,  halfSize), Math3D::Vector3(0,0,1), Math3D::Vector3(1,0,0), Math3D::Vector3(0,1,0), Math3D::Vector2(0,1)));
    
    mesh.vertices.push_back(Vertex(Math3D::Vector3(-halfSize, -halfSize, -halfSize), Math3D::Vector3(0,0,-1), Math3D::Vector3(-1,0,0), Math3D::Vector3(0,1,0), Math3D::Vector2(1,0)));
    mesh.vertices.push_back(Vertex(Math3D::Vector3(-halfSize,  halfSize, -halfSize), Math3D::Vector3(0,0,-1), Math3D::Vector3(-1,0,0), Math3D::Vector3(0,1,0), Math3D::Vector2(1,1)));
    mesh.vertices.push_back(Vertex(Math3D::Vector3( halfSize,  halfSize, -halfSize), Math3D::Vector3(0,0,-1), Math3D::Vector3(-1,0,0), Math3D::Vector3(0,1,0), Math3D::Vector2(0,1)));
    mesh.vertices.push_back(Vertex(Math3D::Vector3( halfSize, -halfSize, -halfSize), Math3D::Vector3(0,0,-1), Math3D::Vector3(-1,0,0), Math3D::Vector3(0,1,0), Math3D::Vector2(0,0)));
    
    mesh.vertices.push_back(Vertex(Math3D::Vector3(-halfSize,  halfSize,  halfSize), Math3D::Vector3(0,1,0), Math3D::Vector3(1,0,0), Math3D::Vector3(0,0,1), Math3D::Vector2(0,1)));
    mesh.vertices.push_back(Vertex(Math3D::Vector3( halfSize,  halfSize,  halfSize), Math3D::Vector3(0,1,0), Math3D::Vector3(1,0,0), Math3D::Vector3(0,0,1), Math3D::Vector2(1,1)));
    mesh.vertices.push_back(Vertex(Math3D::Vector3( halfSize,  halfSize, -halfSize), Math3D::Vector3(0,1,0), Math3D::Vector3(1,0,0), Math3D::Vector3(0,0,1), Math3D::Vector2(1,0)));
    mesh.vertices.push_back(Vertex(Math3D::Vector3(-halfSize, -halfSize,  halfSize), Math3D::Vector3(0,-1,0), Math3D::Vector3(1,0,0), Math3D::Vector3(0,0,-1), Math3D::Vector2(0,0)));
    mesh.vertices.push_back(Vertex(Math3D::Vector3(-halfSize, -halfSize, -halfSize), Math3D::Vector3(0,-1,0), Math3D::Vector3(1,0,0), Math3D::Vector3(0,0,-1), Math3D::Vector2(0,1)));
    mesh.vertices.push_back(Vertex(Math3D::Vector3( halfSize, -halfSize, -halfSize), Math3D::Vector3(0,-1,0), Math3D::Vector3(1,0,0), Math3D::Vector3(0,0,-1), Math3D::Vector2(1,1)));
    mesh.vertices.push_back(Vertex(Math3D::Vector3( halfSize, -halfSize,  halfSize), Math3D::Vector3(0,-1,0), Math3D::Vector3(1,0,0), Math3D::Vector3(0,0,-1), Math3D::Vector2(1,0)));
    
    mesh.vertices.push_back(Vertex(Math3D::Vector3( halfSize, -halfSize,  halfSize), Math3D::Vector3(1,0,0), Math3D::Vector3(0,0,-1), Math3D::Vector3(0,1,0), Math3D::Vector2(0,0)));
    mesh.vertices.push_back(Vertex(Math3D::Vector3( halfSize, -halfSize, -halfSize), Math3D::Vector3(1,0,0), Math3D::Vector3(0,0,-1), Math3D::Vector3(0,1,0), Math3D::Vector2(1,0)));
    mesh.vertices.push_back(Vertex(Math3D::Vector3( halfSize,  halfSize, -halfSize), Math3D::Vector3(1,0,0), Math3D::Vector3(0,0,-1), Math3D::Vector3(0,1,0), Math3D::Vector2(1,1)));
    mesh.vertices.push_back(Vertex(Math3D::Vector3( halfSize,  halfSize,  halfSize), Math3D::Vector3(1,0,0), Math3D::Vector3(0,0,-1), Math3D::Vector3(0,1,0), Math3D::Vector2(0,1)));
    
    mesh.vertices.push_back(Vertex(Math3D::Vector3(-halfSize, -halfSize,  halfSize), Math3D::Vector3(-1,0,0), Math3D::Vector3(0,0,1), Math3D::Vector3(0,1,0), Math3D::Vector2(1,0)));
    mesh.vertices.push_back(Vertex(Math3D::Vector3(-halfSize,  halfSize,  halfSize), Math3D::Vector3(-1,0,0), Math3D::Vector3(0,0,1), Math3D::Vector3(0,1,0), Math3D::Vector2(1,1)));
    mesh.vertices.push_back(Vertex(Math3D::Vector3(-halfSize,  halfSize, -halfSize), Math3D::Vector3(-1,0,0), Math3D::Vector3(0,0,1), Math3D::Vector3(0,1,0), Math3D::Vector2(0,1)));
    mesh.vertices.push_back(Vertex(Math3D::Vector3(-halfSize, -halfSize, -halfSize), Math3D::Vector3(-1,0,0), Math3D::Vector3(0,0,1), Math3D::Vector3(0,1,0), Math3D::Vector2(0,0)));
    
    std::vector<uint32_t> cubeIndices = {
        0, 1, 2,  2, 3, 0,       
        4, 5, 6,  6, 7, 4,       
        8, 9, 10, 10, 11, 8,     
        12, 13, 14, 14, 15, 12,  
        16, 17, 18, 18, 19, 16,  
        20, 21, 22, 22, 23, 20   
    };
    
    mesh.indices = cubeIndices;
    mesh.UpdateBounds();
    return mesh;
}

Mesh Mesh::CreatePlane(float size, uint32_t segments) {
    Mesh mesh;
    segments = std::max(segments, 1u);
    float step = size / segments;
    float halfSize = size * 0.5f;
    
    for (uint32_t z = 0; z <= segments; ++z) {
        for (uint32_t x = 0; x <= segments; ++x) {
            float xPos = -halfSize + x * step;
            float zPos = -halfSize + z * step;
            float u = static_cast<float>(x) / segments;
            float v = static_cast<float>(z) / segments;
            
            mesh.vertices.push_back(Vertex(
                Math3D::Vector3(xPos, 0.0f, zPos),
                Math3D::Vector3(0.0f, 1.0f, 0.0f),  
                Math3D::Vector3(1.0f, 0.0f, 0.0f),  
                Math3D::Vector3(0.0f, 0.0f, 1.0f),  
                Math3D::Vector2(u, v)
            ));
        }
    }
    
    for (uint32_t z = 0; z < segments; ++z) {
        for (uint32_t x = 0; x < segments; ++x) {
            uint32_t topLeft = z * (segments + 1) + x;
            uint32_t topRight = topLeft + 1;
            uint32_t bottomLeft = (z + 1) * (segments + 1) + x;
            uint32_t bottomRight = bottomLeft + 1;
            
            mesh.indices.push_back(topLeft);
            mesh.indices.push_back(bottomLeft);
            mesh.indices.push_back(topRight);
            
            mesh.indices.push_back(topRight);
            mesh.indices.push_back(bottomLeft);
            mesh.indices.push_back(bottomRight);
        }
    }
    
    mesh.UpdateBounds();
    return mesh;
}

Mesh Mesh::CreateSphere(float radius, uint32_t segments) {
    Mesh mesh;
    segments = std::max(segments, 3u);
    
    for (uint32_t y = 0; y <= segments; ++y) {
        float v = static_cast<float>(y) / segments;
        float theta = v * Math3D::MathUtils::PI;
        
        for (uint32_t x = 0; x <= segments; ++x) {
            float u = static_cast<float>(x) / segments;
            float phi = u * Math3D::MathUtils::PI * 2.0f;
            
            float sinTheta = std::sin(theta);
            float cosTheta = std::cos(theta);
            float sinPhi = std::sin(phi);
            float cosPhi = std::cos(phi);
            
            Math3D::Vector3 position(
                radius * sinTheta * cosPhi,
                radius * cosTheta,
                radius * sinTheta * sinPhi
            );
            
            Math3D::Vector3 normal = position.Normalized();
            
            Math3D::Vector3 tangent(
                -radius * sinTheta * sinPhi,
                0.0f,
                radius * sinTheta * cosPhi
            );
            tangent.Normalize();
            
            Math3D::Vector3 bitangent = normal.Cross(tangent).Normalized();
            
            if (y == 0 || y == segments) {
                Math3D::Vector3 arbitrary(1.0f, 0.0f, 0.0f);
                if (std::abs(normal.Dot(arbitrary)) > 0.9f) {
                    arbitrary = Math3D::Vector3(0.0f, 0.0f, 1.0f);
                }
                tangent = (arbitrary - normal * normal.Dot(arbitrary)).Normalized();
                bitangent = normal.Cross(tangent).Normalized();
            }
            
            mesh.vertices.push_back(Vertex(
                position,
                normal,
                tangent,
                bitangent,
                Math3D::Vector2(u, v)
            ));
        }
    }
    
    for (uint32_t y = 0; y < segments; ++y) {
        for (uint32_t x = 0; x < segments; ++x) {
            uint32_t first = y * (segments + 1) + x;
            uint32_t second = first + 1;
            uint32_t third = (y + 1) * (segments + 1) + x;
            uint32_t fourth = third + 1;
            
            mesh.indices.push_back(first);
            mesh.indices.push_back(third);
            mesh.indices.push_back(second);
            
            mesh.indices.push_back(second);
            mesh.indices.push_back(third);
            mesh.indices.push_back(fourth);
        }
    }
    
    mesh.UpdateBounds();
    
    mesh.CalculateTangents();
    
    return mesh;
}

Mesh Mesh::CreateCylinder(float radius, float height, uint32_t segments) {
    Mesh mesh;
    segments = std::max(segments, 3u);
    float halfHeight = height * 0.5f;
    
    for (uint32_t i = 0; i <= segments; ++i) {
        float angle = (static_cast<float>(i) / segments) * Math3D::MathUtils::PI * 2.0f;
        float x = std::cos(angle) * radius;
        float z = std::sin(angle) * radius;
        float u = static_cast<float>(i) / segments;
        
        Math3D::Vector3 normal(x, 0.0f, z);
        normal.Normalize();
        
        Math3D::Vector3 tangent(-std::sin(angle), 0.0f, std::cos(angle));
        tangent.Normalize();
        
        Math3D::Vector3 bitangent(0.0f, 1.0f, 0.0f);
        
        mesh.vertices.push_back(Vertex(
            Math3D::Vector3(x, halfHeight, z),
            normal,
            tangent,
            bitangent,
            Math3D::Vector2(u, 0.0f)
        ));
        
        mesh.vertices.push_back(Vertex(
            Math3D::Vector3(x, -halfHeight, z),
            normal,
            tangent,
            bitangent,
            Math3D::Vector2(u, 1.0f)
        ));
    }
    
    for (uint32_t i = 0; i < segments; ++i) {
        uint32_t topLeft = i * 2;
        uint32_t topRight = topLeft + 2;
        uint32_t bottomLeft = topLeft + 1;
        uint32_t bottomRight = topRight + 1;
        
        mesh.indices.push_back(topLeft);
        mesh.indices.push_back(bottomLeft);
        mesh.indices.push_back(topRight);
        
        mesh.indices.push_back(topRight);
        mesh.indices.push_back(bottomLeft);
        mesh.indices.push_back(bottomRight);
    }
    
    uint32_t topCenterIndex = static_cast<uint32_t>(mesh.vertices.size());
    mesh.vertices.push_back(Vertex(
        Math3D::Vector3(0.0f, halfHeight, 0.0f),
        Math3D::Vector3(0.0f, 1.0f, 0.0f),  
        Math3D::Vector3(1.0f, 0.0f, 0.0f),  
        Math3D::Vector3(0.0f, 0.0f, 1.0f),  
        Math3D::Vector2(0.5f, 0.5f)
    ));
    
    for (uint32_t i = 0; i <= segments; ++i) {
        float angle = (static_cast<float>(i) / segments) * Math3D::MathUtils::PI * 2.0f;
        float x = std::cos(angle) * radius;
        float z = std::sin(angle) * radius;
        float u = (std::cos(angle) + 1.0f) * 0.5f;
        float v = (std::sin(angle) + 1.0f) * 0.5f;
        
        mesh.vertices.push_back(Vertex(
            Math3D::Vector3(x, halfHeight, z),
            Math3D::Vector3(0.0f, 1.0f, 0.0f),
            Math3D::Vector3(1.0f, 0.0f, 0.0f),
            Math3D::Vector3(0.0f, 0.0f, 1.0f),
            Math3D::Vector2(u, v)
        ));
    }
    
    for (uint32_t i = 0; i < segments; ++i) {
        mesh.indices.push_back(topCenterIndex);
        mesh.indices.push_back(topCenterIndex + i + 1);
        mesh.indices.push_back(topCenterIndex + i + 2);
    }
    
    uint32_t bottomCenterIndex = static_cast<uint32_t>(mesh.vertices.size());
    mesh.vertices.push_back(Vertex(
        Math3D::Vector3(0.0f, -halfHeight, 0.0f),
        Math3D::Vector3(0.0f, -1.0f, 0.0f),  
        Math3D::Vector3(1.0f, 0.0f, 0.0f),   
        Math3D::Vector3(0.0f, 0.0f, -1.0f),  
        Math3D::Vector2(0.5f, 0.5f)
    ));
    
    for (uint32_t i = 0; i <= segments; ++i) {
        float angle = (static_cast<float>(i) / segments) * Math3D::MathUtils::PI * 2.0f;
        float x = std::cos(angle) * radius;
        float z = std::sin(angle) * radius;
        float u = (std::cos(angle) + 1.0f) * 0.5f;
        float v = (std::sin(angle) + 1.0f) * 0.5f;
        
        mesh.vertices.push_back(Vertex(
            Math3D::Vector3(x, -halfHeight, z),
            Math3D::Vector3(0.0f, -1.0f, 0.0f),
            Math3D::Vector3(1.0f, 0.0f, 0.0f),
            Math3D::Vector3(0.0f, 0.0f, -1.0f),
            Math3D::Vector2(u, v)
        ));
    }
    
    for (uint32_t i = 0; i < segments; ++i) {
        mesh.indices.push_back(bottomCenterIndex);
        mesh.indices.push_back(bottomCenterIndex + i + 2);
        mesh.indices.push_back(bottomCenterIndex + i + 1);
    }
    
    mesh.UpdateBounds();
    
    mesh.CalculateTangents();
    
    return mesh;
}

} 
