#include "Geometry/BoundingBox.h"
#include "Math3D/MathUtils.h"
#include <limits>
#include <algorithm>

using Math3D::Vector3;

namespace Geometry {

BoundingBox::BoundingBox() {
    Reset();
}

BoundingBox::BoundingBox(const Vector3& min, const Vector3& max) 
    : min(min), max(max) {
}

BoundingBox::BoundingBox(const Vector3& center, float radius) {
    min = center - Vector3(radius, radius, radius);
    max = center + Vector3(radius, radius, radius);
}

void BoundingBox::Expand(const Vector3& point) {
    if (!IsValid()) {
        min = max = point;
        return;
    }
    
    min.x = std::min(min.x, point.x);
    min.y = std::min(min.y, point.y);
    min.z = std::min(min.z, point.z);
    
    max.x = std::max(max.x, point.x);
    max.y = std::max(max.y, point.y);
    max.z = std::max(max.z, point.z);
}

void BoundingBox::Expand(const BoundingBox& other) {
    if (!other.IsValid()) return;
    
    Expand(other.min);
    Expand(other.max);
}

Vector3 BoundingBox::GetCenter() const {
    if (!IsValid()) return Vector3::Zero;
    return (min + max) * 0.5f;
}

Vector3 BoundingBox::GetSize() const {
    if (!IsValid()) return Vector3::Zero;
    return max - min;
}

float BoundingBox::GetRadius() const {
    if (!IsValid()) return 0.0f;
    return GetSize().Length() * 0.5f;
}

bool BoundingBox::Contains(const Vector3& point) const {
    if (!IsValid()) return false;
    
    return point.x >= min.x && point.x <= max.x &&
           point.y >= min.y && point.y <= max.y &&
           point.z >= min.z && point.z <= max.z;
}

bool BoundingBox::Intersects(const BoundingBox& other) const {
    if (!IsValid() || !other.IsValid()) return false;
    
    return !(max.x < other.min.x || min.x > other.max.x ||
             max.y < other.min.y || min.y > other.max.y ||
             max.z < other.min.z || min.z > other.max.z);
}

bool BoundingBox::IsValid() const {
    return min.x <= max.x && min.y <= max.y && min.z <= max.z;
}

void BoundingBox::Reset() {
    float maxFloat = std::numeric_limits<float>::max();
    float minFloat = std::numeric_limits<float>::lowest();
    
    min = Vector3(maxFloat, maxFloat, maxFloat);
    max = Vector3(minFloat, minFloat, minFloat);
}

BoundingBox BoundingBox::FromPoints(const Vector3* points, size_t count) {
    BoundingBox box;
    for (size_t i = 0; i < count; ++i) {
        box.Expand(points[i]);
    }
    return box;
}

BoundingBox BoundingBox::Zero() {
    return BoundingBox(Vector3::Zero, Vector3::Zero);
}

BoundingBox BoundingBox::Unit() {
    return BoundingBox(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.5f, 0.5f, 0.5f));
}

} 
