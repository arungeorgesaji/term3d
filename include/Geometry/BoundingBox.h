#pragma once
#include "Math3D/Vector3.h"
#include <cstddef>

namespace Geometry {

class BoundingBox {
public:
    Math3D::Vector3 min;
    Math3D::Vector3 max;
    
    BoundingBox();
    BoundingBox(const Math3D::Vector3& min, const Math3D::Vector3& max);
    BoundingBox(const Math3D::Vector3& center, float radius);
    
    void Expand(const Math3D::Vector3& point);
    void Expand(const BoundingBox& other);
    
    Math3D::Vector3 GetCenter() const;
    Math3D::Vector3 GetSize() const;
    float GetRadius() const;
    
    bool Contains(const Math3D::Vector3& point) const;
    bool Intersects(const BoundingBox& other) const;
    
    bool IsValid() const;
    void Reset();
    
    static BoundingBox FromPoints(const Math3D::Vector3* points, size_t count);
    
    static BoundingBox Zero();
    static BoundingBox Unit();
};

} 
