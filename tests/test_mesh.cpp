#include <iostream>
#include "../include/Geometry/Mesh.h"
#include "../include/Math3D/MathUtils.h"

using namespace Geometry;
using namespace Math3D;

void TestVertexStructure() {
    std::cout << "Testing Vertex Structure..." << std::endl;
    
    Vertex vertex(
        Vector3(1.0f, 2.0f, 3.0f),    
        Vector3(0.0f, 1.0f, 0.0f),      
        Vector3(1.0f, 0.0f, 0.0f),      
        Vector3(0.0f, 0.0f, 1.0f),    
        Vector2(0.5f, 0.5f)             
    );
    
    if (vertex.position == Vector3(1.0f, 2.0f, 3.0f) &&
        vertex.normal == Vector3(0.0f, 1.0f, 0.0f) &&
        vertex.tangent == Vector3(1.0f, 0.0f, 0.0f) &&
        vertex.bitangent == Vector3(0.0f, 0.0f, 1.0f) &&
        vertex.texCoord == Vector2(0.5f, 0.5f)) {
        std::cout << "Vertex structure test passed" << std::endl;
    } else {
        std::cout << "Vertex structure test failed" << std::endl;
    }
}

void TestMeshCreation() {
    std::cout << "Testing Mesh Creation..." << std::endl;
    
    Mesh emptyMesh;
    if (!emptyMesh.IsValid()) {
        std::cout << "Empty mesh test passed" << std::endl;
    } else {
        std::cout << "Empty mesh test failed" << std::endl;
    }
    
    std::vector<Vertex> vertices = {
        Vertex(Vector3(-1.0f, -1.0f, 0.0f)),
        Vertex(Vector3(1.0f, -1.0f, 0.0f)),
        Vertex(Vector3(0.0f, 1.0f, 0.0f))
    };
    std::vector<uint32_t> indices = {0, 1, 2};
    
    Mesh triangleMesh(vertices, indices);
    if (triangleMesh.IsValid() && triangleMesh.GetTriangleCount() == 1) {
        std::cout << "Triangle mesh test passed" << std::endl;
    } else {
        std::cout << "Triangle mesh test failed" << std::endl;
    }
}

void TestNormalCalculation() {
    std::cout << "Testing Normal Calculation..." << std::endl;
    
    Mesh mesh = Mesh::CreateCube(2.0f);
    mesh.CalculateNormals();
    
    bool hasValidNormals = true;
    for (const auto& vertex : mesh.vertices) {
        if (vertex.normal.LengthSquared() < 0.9f) {
            hasValidNormals = false;
            break;
        }
    }
    
    if (hasValidNormals) {
        std::cout << "Normal calculation test passed" << std::endl;
    } else {
        std::cout << "Normal calculation test failed" << std::endl;
    }
}

void TestTangentCalculation() {
    std::cout << "Testing Tangent Calculation..." << std::endl;
    
    std::vector<Vertex> vertices = {
        Vertex(Vector3(-1.0f, -1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f)),
        Vertex(Vector3(1.0f, -1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector2(1.0f, 0.0f)),
        Vertex(Vector3(1.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f)),
        Vertex(Vector3(-1.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f))
    };
    
    std::vector<uint32_t> indices = {0, 1, 2, 2, 3, 0};
    Mesh mesh(vertices, indices);
    
    mesh.CalculateTangents();
    
    bool validTangentSpace = true;
    for (const auto& vertex : mesh.vertices) {
        float dotNT = vertex.normal.Dot(vertex.tangent);
        float dotNB = vertex.normal.Dot(vertex.bitangent);
        
        if (std::abs(dotNT) > 0.01f || std::abs(dotNB) > 0.01f) {
            validTangentSpace = false;
            break;
        }
    }
    
    if (validTangentSpace) {
        std::cout << "Tangent calculation test passed" << std::endl;
    } else {
        std::cout << "Tangent calculation test failed" << std::endl;
    }
}

void TestPrimitiveGeneration() {
    std::cout << "Testing Primitive Generation..." << std::endl;
    
    Mesh cube = Mesh::CreateCube(2.0f);
    if (cube.IsValid() && cube.GetVertexCount() == 24 && cube.GetTriangleCount() == 12) {
        std::cout << "Cube generation test passed" << std::endl;
    } else {
        std::cout << "Cube generation test failed" << std::endl;
    }
    
    Mesh plane = Mesh::CreatePlane(4.0f, 2);
    if (plane.IsValid() && plane.GetVertexCount() == 9 && plane.GetTriangleCount() == 8) {
        std::cout << "Plane generation test passed" << std::endl;
    } else {
        std::cout << "Plane generation test failed" << std::endl;
    }
    
    Mesh sphere = Mesh::CreateSphere(1.0f, 8);
    if (sphere.IsValid() && sphere.GetVertexCount() == 81) {
        std::cout << "Sphere generation test passed" << std::endl;
    } else {
        std::cout << "Sphere generation test failed" << std::endl;
    }
    
    Mesh cylinder = Mesh::CreateCylinder(0.5f, 2.0f, 8);
    if (cylinder.IsValid()) {
        std::cout << "Cylinder generation test passed" << std::endl;
    } else {
        std::cout << "Cylinder generation test failed" << std::endl;
    }
}

void TestMeshTransformation() {
    std::cout << "Testing Mesh Transformation..." << std::endl;
    
    Mesh cube = Mesh::CreateCube(1.0f);
    Vector3 originalCenter = cube.bounds.GetCenter();
    
    Matrix4 translation = Matrix4::Translation(Vector3(3.0f, 0.0f, 0.0f));
    cube.Transform(translation);
    
    Vector3 newCenter = cube.bounds.GetCenter();
    Vector3 expectedCenter = originalCenter + Vector3(3.0f, 0.0f, 0.0f);
    
    if (MathUtils::Approximately(newCenter.x, expectedCenter.x, 0.001f)) {
        std::cout << "Mesh transformation test passed" << std::endl;
    } else {
        std::cout << "Mesh transformation test failed" << std::endl;
    }
}

void TestBoundsCalculation() {
    std::cout << "Testing Bounds Calculation..." << std::endl;
    
    Mesh cube = Mesh::CreateCube(2.0f);
    
    if (cube.bounds.IsValid() && 
        cube.bounds.GetCenter() == Vector3::Zero &&
        cube.bounds.GetSize() == Vector3(2.0f, 2.0f, 2.0f)) {
        std::cout << "Bounds calculation test passed" << std::endl;
    } else {
        std::cout << "Bounds calculation test failed" << std::endl;
    }
}

void TestPrimitiveTangentSpaces() {
    std::cout << "Testing Primitive Tangent Spaces..." << std::endl;
    
    bool allPrimitivesValid = true;
    
    Mesh primitives[] = {
        Mesh::CreateCube(1.0f),
        Mesh::CreatePlane(2.0f, 2),
        Mesh::CreateSphere(1.0f, 8),
        Mesh::CreateCylinder(0.5f, 2.0f, 8)
    };
    
    const char* names[] = {"Cube", "Plane", "Sphere", "Cylinder"};
    
    for (int i = 0; i < 4; ++i) {
        bool validTangentSpace = true;
        
        for (const auto& vertex : primitives[i].vertices) {
            if (vertex.normal.LengthSquared() < 0.1f || 
                vertex.tangent.LengthSquared() < 0.1f ||
                vertex.bitangent.LengthSquared() < 0.1f) {
                continue;
            }
            
            float dotNT = vertex.normal.Dot(vertex.tangent);
            float dotNB = vertex.normal.Dot(vertex.bitangent);
            
            if (std::abs(dotNT) > 0.1f || std::abs(dotNB) > 0.1f) {
                validTangentSpace = false;
                break;
            }
        }
        
        if (validTangentSpace) {
            std::cout << names[i] << " tangent space test passed" << std::endl;
        } else {
            std::cout << names[i] << " tangent space test failed" << std::endl;
            allPrimitivesValid = false;
        }
    }
    
    if (allPrimitivesValid) {
        std::cout << "All primitives have valid tangent spaces" << std::endl;
    }
}

int main() {
    std::cout << "=== Running Mesh Tests ===" << std::endl;
    
    TestVertexStructure();
    TestMeshCreation();
    TestNormalCalculation();
    TestTangentCalculation();
    TestPrimitiveGeneration();
    TestMeshTransformation();
    TestBoundsCalculation();
    TestPrimitiveTangentSpaces();
    
    std::cout << "=== Mesh Tests Complete ===" << std::endl;
    return 0;
}
