#version 330 core
out vec3 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gDiffuseColor;
uniform sampler2D gSpecularColor;
uniform sampler2D gAmbientColor;

struct Light {
    vec3 Position;
    vec3 Color;

    float Linear;
    float Quadratic;
};
const int NR_LIGHTS = 32;
uniform Light lights[NR_LIGHTS];
uniform int actLightNumber;
uniform vec3 viewPos;

void main()
{
    // retrieve data from gbuffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gDiffuseColor, TexCoords).rgb;
    vec3 Specular = texture(gSpecularColor, TexCoords).rgb;
    vec3 Ambient = texture(gAmbientColor, TexCoords).rgb;

    // then calculate lighting as usual
    vec3 lighting  = Ambient;
    vec3 viewDir  = normalize(viewPos - FragPos);
    for(int i = 0; i < actLightNumber; ++i)
    {
        // diffuse
        vec3 lightDir = normalize(lights[i].Position - FragPos);
        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * lights[i].Color;
        // specular
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
        vec3 specular = lights[i].Color * spec * Specular;
        // attenuation
        float distance = length(lights[i].Position - FragPos);
        float attenuation = 1.0 / (1.0 + lights[i].Linear * distance + lights[i].Quadratic * distance * distance);
        diffuse *= attenuation;
        specular *= attenuation;
        lighting += diffuse + specular;
    }
    float gamma = 2.2;
    vec4 color = vec4(lighting, 1.0);
    FragColor.rgb = pow(color.rgb, vec3(1.0/gamma));
}



//#version 330 core
//out vec4 FragColor;
//
//in vec2 TexCoords;
//
//uniform sampler2D gPosition;
//uniform sampler2D gNormal;
//uniform sampler2D gDiffuseColor;
//uniform sampler2D gSpecularColor;
//uniform sampler2D gAmbientColor;
//
//uniform vec3 Position;
//uniform vec3 Color;
//
//uniform float Linear;
//uniform float Quadratic;
//uniform int actLightsNumber;
//uniform vec3 viewPos;
//
//void main()
//{
//    // retrieve data from gbuffer
//    vec3 FragPos = texture(gPosition, TexCoords).rgb;
//    vec3 Normal = texture(gNormal, TexCoords).rgb;
//    vec3 Diffuse = texture(gDiffuseColor, TexCoords).rgb;
//    vec3 Specular = texture(gSpecularColor, TexCoords).rgb;
//    vec3 Ambient = texture(gAmbientColor, TexCoords).rgb;
//
//    // then calculate lighting as usual
//    vec3 lighting  = Ambient;
//    vec3 viewDir  = normalize(viewPos - FragPos);
//
//    // diffuse
//    vec3 lightDir = normalize(Position - FragPos);
//    vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * Color;
//    // specular
//    vec3 halfwayDir = normalize(lightDir + viewDir);
//    float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
//    vec3 specular = Color * spec * Specular;
//    // attenuation
//    float distance = length(Position - FragPos);
//    float attenuation = 1.0 / (1.0 + Linear * distance + Quadratic * distance * distance);
//    diffuse *= attenuation;
//    specular *= attenuation;
//    lighting += diffuse + specular;
//    FragColor = vec4(lighting, 1.0);
//}