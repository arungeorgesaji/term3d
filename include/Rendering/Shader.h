#pragma once
#include <string>
#include <unordered_map>
#include <GL/glew.h>
#include "Math3D/Matrix4.h"
#include "Math3D/Vector3.h"
#include "Math3D/Vector4.h"

namespace Rendering {

class Shader {
private:
    GLuint m_programID;
    std::string m_name;
    std::unordered_map<std::string, GLint> m_uniformCache;
    
    bool CompileShader(GLuint& shader, GLenum type, const std::string& source);
    bool LinkProgram();
    GLint GetUniformLocation(const std::string& name);

public:
    Shader();
    ~Shader();
    
    bool LoadFromSource(const std::string& name, 
                       const std::string& vertexSource, 
                       const std::string& fragmentSource);
    
    bool LoadFromFile(const std::string& name,
                     const std::string& vertexPath,
                     const std::string& fragmentPath);
    
    void Use() const;
    void Unuse() const;
    
    void SetUniform(const std::string& name, float value);
    void SetUniform(const std::string& name, int value);
    void SetUniform(const std::string& name, const Math3D::Vector3& value);
    void SetUniform(const std::string& name, const Math3D::Vector4& value);
    void SetUniform(const std::string& name, const Math3D::Matrix4& value);
    void SetUniform(const std::string& name, bool value);
    
    GLuint GetProgramID() const { return m_programID; }
    const std::string& GetName() const { return m_name; }
    bool IsValid() const { return m_programID != 0; }
};

}
