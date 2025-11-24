cmake_minimum_required(VERSION 3.15)
project(Term3D_Demos)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    Term3D
    GIT_REPOSITORY https://github.com/arungeorgesaji/Term3D.git
    GIT_TAG v1.0.0
)
FetchContent_MakeAvailable(Term3D)

find_package(glfw3 REQUIRED)

add_executable(SimpleCubeDemo simple_cube.cpp)
target_link_libraries(SimpleCubeDemo Term3D glfw)

add_executable(TransformationChainDemo transformation_chain.cpp)
target_link_libraries(TransformationChainDemo Term3D glfw)

add_executable(RealtimeMeshDemo realtime_mesh.cpp)
target_link_libraries(RealtimeMeshDemo Term3D glfw)
