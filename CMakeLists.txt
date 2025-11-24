cmake_minimum_required(VERSION 3.15)
project(Term3D VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TERM3D_BUILD_TESTS "Build tests" OFF)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

add_library(Term3D
    src/Math3D/Vector2.cpp
    src/Math3D/Vector3.cpp
    src/Math3D/Vector4.cpp
    src/Math3D/Matrix3.cpp
    src/Math3D/Matrix4.cpp
    src/Math3D/MathUtils.cpp
    src/Geometry/BoundingBox.cpp
    src/Geometry/Mesh.cpp
    src/Rendering/OpenGLRenderer.cpp
    src/Core/GraphicsEngine.cpp
)

target_include_directories(Term3D PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(Term3D PUBLIC
    OpenGL::GL 
    GLEW::GLEW
)

if(TERM3D_BUILD_TESTS)
    add_executable(MathTest tests/test_math.cpp)
    target_link_libraries(MathTest Term3D)
    
    add_executable(MatrixTest tests/test_matrix.cpp)
    target_link_libraries(MatrixTest Term3D)
    
    add_executable(InversionTest tests/test_matrix_inversion.cpp)
    target_link_libraries(InversionTest Term3D)
    
    add_executable(GeometryBasicTest tests/test_geometry_basic.cpp)
    target_link_libraries(GeometryBasicTest Term3D)
    
    add_executable(MeshTest tests/test_mesh.cpp)
    target_link_libraries(MeshTest Term3D)
    
    add_executable(RendererInterfaceTest tests/test_renderer_interface.cpp)
    target_link_libraries(RendererInterfaceTest Term3D)
endif()
