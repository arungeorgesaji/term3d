#pragma once
#include "Rendering/Shader.h"
#include <unordered_map>
#include <memory>

namespace Rendering {

class ShaderManager {
private:
    std::unordered_map<std::string, std::unique_ptr<Shader>> m_shaders;
    
public:
    ShaderManager() = default;
    ~ShaderManager() = default;
    
    Shader* LoadShader(const std::string& name,
                      const std::string& vertexPath,
                      const std::string& fragmentPath);
    
    Shader* GetShader(const std::string& name);
    bool HasShader(const std::string& name) const;
    void ReloadAllShaders();
    
    Shader* GetDefaultShader();
    Shader* GetUnlitShader();
    Shader* GetWireframeShader();
};

} 
