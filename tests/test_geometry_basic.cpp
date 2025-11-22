#include <iostream>
#include "../include/Geometry/Vertex.h"
#include "../include/Geometry/BoundingBox.h"
#include "../include/Math3D/MathUtils.h"

using namespace Geometry;
using namespace Math3D;

void TestVertex() {
    std::cout << "Testing Vertex..." << std::endl;
    
    Vertex v1;
    if (v1.position == Vector3::Zero && v1.normal == Vector3(0,1,0) && v1.texCoord == Vector2::Zero) {
        std::cout << "Default vertex constructor test passed" << std::endl;
    } else {
        std::cout << "Default vertex constructor test failed" << std::endl;
    }
    
    Vector3 pos(1.0f, 2.0f, 3.0f);
    Vector3 norm(0.0f, 1.0f, 0.0f);
    Vector2 tex(0.5f, 0.5f);
    Vertex v2(pos, norm, tex);
    
    if (v2.position == pos && v2.normal == norm && v2.texCoord == tex) {
        std::cout << "Parameterized vertex constructor test passed" << std::endl;
    } else {
        std::cout << "Parameterized vertex constructor test failed" << std::endl;
    }
    
    Vertex v3(pos, norm, tex);
    if (v2 == v3) {
        std::cout << "Vertex equality test passed" << std::endl;
    } else {
        std::cout << "Vertex equality test failed" << std::endl;
    }
}

void TestBoundingBox() {
    std::cout << "Testing BoundingBox..." << std::endl;
    
    BoundingBox box1;
    if (!box1.IsValid()) {
        std::cout << "Default bounding box test passed" << std::endl;
    } else {
        std::cout << "Default bounding box test failed" << std::endl;
    }
    
    BoundingBox box2(Vector3(-1, -1, -1), Vector3(1, 1, 1));
    if (box2.IsValid() && box2.GetCenter() == Vector3::Zero) {
        std::cout << "Min/max bounding box test passed" << std::endl;
    } else {
        std::cout << "Min/max bounding box test failed" << std::endl;
    }
    
    BoundingBox box3;
    box3.Expand(Vector3(0, 0, 0));
    box3.Expand(Vector3(2, 2, 2));
    
    if (box3.min == Vector3(0, 0, 0) && box3.max == Vector3(2, 2, 2)) {
        std::cout << "Bounding box expansion test passed" << std::endl;
    } else {
        std::cout << "Bounding box expansion test failed" << std::endl;
    }
    
    BoundingBox box4(Vector3(-1, -1, -1), Vector3(1, 1, 1));
    if (box4.Contains(Vector3(0, 0, 0)) && !box4.Contains(Vector3(2, 2, 2))) {
        std::cout << "Bounding box containment test passed" << std::endl;
    } else {
        std::cout << "Bounding box containment test failed" << std::endl;
    }
    
    BoundingBox box5(Vector3(0, 0, 0), Vector3(2, 2, 2));
    BoundingBox box6(Vector3(1, 1, 1), Vector3(3, 3, 3));
    if (box5.Intersects(box6)) {
        std::cout << "Bounding box intersection test passed" << std::endl;
    } else {
        std::cout << "Bounding box intersection test failed" << std::endl;
    }
}

int main() {
    TestVertex();
    TestBoundingBox();
    return 0;
}
