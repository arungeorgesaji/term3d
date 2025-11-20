cmake_minimum_required(VERSION 3.15)
project(Math3D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(Math3D
    src/Math3D/Vector2.cpp
    src/Math3D/Vector3.cpp
    src/Math3D/Vector4.cpp
    src/Math3D/MathUtils.cpp
)

add_executable(MathTest tests/test_math.cpp)
target_link_libraries(MathTest Math3D)
