#include "Rendering/OpenGLRenderer.h"
#include "Geometry/Mesh.h"
#include "Math3D/MathUtils.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Rendering {

const char* BASIC_VERTEX_SHADER = R"(
#version 330 core
layout(location = 0) in vec3 aPosition;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main() {
    gl_Position = uModel * vec4(aPosition, 1.0);
}
)";

const char* BASIC_FRAGMENT_SHADER = R"(
#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(1.0, 0.0, 0.0, 1.0); 
}
)";

OpenGLRenderer::OpenGLRenderer() 
    : m_window(nullptr), m_width(0), m_height(0), m_shaderProgram(0) {
}

OpenGLRenderer::~OpenGLRenderer() {
    Shutdown();
}

bool OpenGLRenderer::Initialize(int width, int height) {
    m_width = width;
    m_height = height;

    if (!glfwInit()) {
        std::cerr << "GLFW init failed" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    m_window = glfwCreateWindow(width, height, "Term3D - WORKING", nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Window creation failed" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW init failed" << std::endl;
        return false;
    }

    const char* vs = BASIC_VERTEX_SHADER;
    const char* fs = BASIC_FRAGMENT_SHADER;
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vs, NULL);
    glCompileShader(vertexShader);
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fs, NULL);
    glCompileShader(fragmentShader);
    
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f); 
    glEnable(GL_DEPTH_TEST);
    
    std::cout << "RENDERER INITIALIZED" << std::endl;
    return true;
}

void OpenGLRenderer::Shutdown() {
    if (m_shaderProgram) glDeleteProgram(m_shaderProgram);
    if (m_window) glfwDestroyWindow(m_window);
    glfwTerminate();
}

void OpenGLRenderer::BeginFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::EndFrame() {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void OpenGLRenderer::DrawMesh(const Geometry::Mesh& mesh, const Math3D::Matrix4& transform) {
    static bool firstTime = true;
    static GLuint vao, vbo, ebo;
    
    if (firstTime) {
        firstTime = false;
        
        const auto& vertices = mesh.vertices;
        const auto& indices = mesh.indices;
        
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, 
                     vertices.size() * sizeof(Geometry::Vertex), 
                     vertices.data(), 
                     GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                     indices.size() * sizeof(uint32_t), 
                     indices.data(), 
                     GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    glUseProgram(m_shaderProgram);
    
    GLuint modelLoc = glGetUniformLocation(m_shaderProgram, "uModel");
    
    if (modelLoc != -1) {
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, transform.Data());
    }
    
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void OpenGLRenderer::DrawMesh(const Geometry::Mesh& mesh) {
    DrawMesh(mesh, Math3D::Matrix4::Identity());
}

void OpenGLRenderer::Clear(ClearFlags flags, const Color& color) {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::SetRenderState(RenderState state) {}
void OpenGLRenderer::EnableState(RenderState state) {}
void OpenGLRenderer::DisableState(RenderState state) {}
void OpenGLRenderer::SetViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}
void OpenGLRenderer::SetProjectionMatrix(const Math3D::Matrix4& projection) {}
void OpenGLRenderer::SetViewMatrix(const Math3D::Matrix4& view) {}
void OpenGLRenderer::Resize(int width, int height) {
    m_width = width; 
    m_height = height;
    glViewport(0, 0, width, height);
}
bool OpenGLRenderer::ShouldClose() const { 
    return m_window ? glfwWindowShouldClose(m_window) : true; 
}

} 
