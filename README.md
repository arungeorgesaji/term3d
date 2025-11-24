# Term3D

<p align="center">
  <img src="https://raw.githubusercontent.com/arungeorgesaji/term3d/main/term3d.gif" width="600" alt="Term3D Demo">
</p>

A lightweight 3D graphics engine built with C++ and OpenGL, designed for real-time rendering and geometric transformations.

## Overview

Term3D is a minimalist 3D rendering framework that provides core functionality for creating and manipulating 3D meshes with matrix transformations. It features a clean API for building interactive 3D applications.

## Features

- **Core 3D Mathematics**: Vector2/3/4, Matrix3/4 with full transformation support
- **Geometric Primitives**: Cube, Sphere, and Plane mesh generation
- **Real-time Rendering**: OpenGL-based renderer with modern shader pipeline
- **Transform System**: Translation, rotation, scaling, and matrix chaining
- **Mesh Management**: Dynamic mesh creation and modification
- **Bounding Box**: Collision detection support

## Usage

Add to your CMakeLists.txt:
```cmake
include(FetchContent)
FetchContent_Declare(
    Term3D
    GIT_REPOSITORY https://github.com/arungeorgesaji/Term3D.git
    GIT_TAG v1.0.0
)
FetchContent_MakeAvailable(Term3D)

target_link_libraries(YourApp Term3D)
```

## Requirements
- OpenGL
- GLEW
- GLFW3 (for demos only)

> Check out /demo for examples on how to use Term3D. 
> The library was made for siege during my exam week and is not worked on much and is not ready for any real use. As it has very limited features and documentation.
