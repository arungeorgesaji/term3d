#version 330 core

in vec3 vNormal;
in vec3 vFragPos;
in vec2 vTexCoord;

out vec4 FragColor;

uniform vec3 uColor;
uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform vec3 uViewPos;

void main() {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * uLightColor;
    
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(uLightPos - vFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * uLightColor;
    
    float specularStrength = 0.5;
    vec3 viewDir = normalize(uViewPos - vFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * uLightColor;
    
    vec3 result = (ambient + diffuse + specular) * uColor;
    FragColor = vec4(result, 1.0);
}
