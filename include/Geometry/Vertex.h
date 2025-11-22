#pragma once
#include "Math3D/Vector3.h"
#include "Math3D/Vector2.h"

namespace Geometry {

struct Vertex {
    Math3D::Vector3 position;
    Math3D::Vector3 normal;
    Math3D::Vector2 texCoord;
    
    Vertex() = default;
    Vertex(const Math3D::Vector3& pos, const Math3D::Vector3& norm = Math3D::Vector3(0,1,0), 
           const Math3D::Vector2& tex = Math3D::Vector2(0,0))
        : position(pos), normal(norm), texCoord(tex) {}
        
    bool operator==(const Vertex& other) const {
        return position == other.position && 
               normal == other.normal && 
               texCoord == other.texCoord;
    }
    
    bool operator!=(const Vertex& other) const {
        return !(*this == other);
    }
};

} 
