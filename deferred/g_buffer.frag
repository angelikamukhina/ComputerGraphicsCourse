#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec3 gDiffuseColor;
layout (location = 3) out vec3 gSpecularColor;
layout (location = 4) out vec3 gAmbientColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 ambient;

void main()
{    
    gPosition = FragPos;
    gNormal = normalize(Normal);
    gDiffuseColor = diffuse;
    gSpecularColor = specular;
    gAmbientColor = ambient;
}