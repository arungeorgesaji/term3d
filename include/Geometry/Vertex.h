#pragma once
#include "Math3D/Vector3.h"
#include "Math3D/Vector2.h"
#include "Math3D/Matrix3.h"
#include "Math3D/Matrix4.h"

namespace Geometry {

struct Vertex {
    Math3D::Vector3 position;
    Math3D::Vector3 normal;
    Math3D::Vector3 tangent;
    Math3D::Vector3 bitangent;
    Math3D::Vector2 texCoord;
    
    Vertex() = default;
    
    explicit Vertex(const Math3D::Vector3& pos)
        : position(pos), 
          normal(Math3D::Vector3(0,1,0)),
          tangent(Math3D::Vector3(1,0,0)), 
          bitangent(Math3D::Vector3(0,0,1)), 
          texCoord(Math3D::Vector2(0,0)) {}
    
    Vertex(const Math3D::Vector3& pos,
           const Math3D::Vector3& norm,
           const Math3D::Vector2& tex)
        : position(pos), normal(norm), 
          tangent(Math3D::Vector3(1,0,0)), 
          bitangent(Math3D::Vector3(0,0,1)), 
          texCoord(tex) {}
    
    Vertex(const Math3D::Vector3& pos,
           const Math3D::Vector3& norm,
           const Math3D::Vector3& tan,
           const Math3D::Vector3& bitan,
           const Math3D::Vector2& tex)
        : position(pos), normal(norm), tangent(tan), bitangent(bitan), texCoord(tex) {}
        
    bool operator==(const Vertex& other) const {
        return position == other.position && 
               normal == other.normal && 
               tangent == other.tangent &&
               bitangent == other.bitangent &&
               texCoord == other.texCoord;
    }
    
    bool operator!=(const Vertex& other) const {
        return !(*this == other);
    }
};

}
