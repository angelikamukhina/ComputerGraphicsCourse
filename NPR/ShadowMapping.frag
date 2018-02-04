#version 330 core

in vec3 Normal_cameraspace;
in vec3 vertexPosition_cameraspace;
in vec3 Position_worldspace;

out vec3 color;

// Values that stay constant for the whole mesh.
uniform mat4 M;
uniform mat4 V;
uniform vec3 MaterialDiffuseColor;
uniform vec3 MaterialAmbientColor;
uniform vec3 MaterialSpecularColor;

uniform vec3 LightPosition;
uniform mat4 DepthBiasVP;
uniform sampler2DShadow shadowMap;

float shininess = 16.0;

void main(){
    vec3 normal = normalize(Normal_cameraspace);
    vec3 LightColor = vec3(1.0f);

    vec3 LightPosition_cameraspace = ( V * vec4(LightPosition, 1)).xyz;
    vec3 LightDir_cameraspace = LightPosition_cameraspace - vertexPosition_cameraspace;

    vec4 ShadowCoord = DepthBiasVP * vec4(Position_worldspace, 1);
    vec3 normLightDir_cameraspace = normalize(LightDir_cameraspace);

    float lambertian =  max(dot(normLightDir_cameraspace, normal), 0.0);

    float specular  = 0.0;
    if (lambertian > 0.0) {
        vec3 viewDir = normalize(-vertexPosition_cameraspace);
        vec3 halfDir = normalize(normLightDir_cameraspace + viewDir);
        float specAngle = max(dot(halfDir, Normal_cameraspace), 0.0);
        specular = pow(specAngle, shininess);
    }

     // variable bias
    float bias = 0.005 * tan(acos(lambertian));
    float visibility = texture(shadowMap, vec3(ShadowCoord.xy,  (ShadowCoord.z - bias)/ShadowCoord.w));
    const float A = 0.1;
    const float B = 0.3;
    const float C = 0.6;
    const float D = 1.0;
    if (lambertian < A) lambertian = 0.0;
    else if (lambertian < B) lambertian = B;
    else if (lambertian < C) lambertian = C;
    else lambertian = D;

    if (visibility < A) visibility = 0.0;
    else if (visibility < B) visibility = B;
    else if (visibility < C) visibility = C;
    else visibility = D;

    if (specular < A) specular = 0.0;
    else if (specular < B) specular = B;
    else if (specular < C) specular = C;
    else specular = D;

    vec3 diffuseMultiplier = visibility * lambertian * LightColor;
    vec3 specularMultiplier = visibility * specular * LightColor;


	color = min(MaterialAmbientColor +
	    MaterialDiffuseColor * diffuseMultiplier +
	    MaterialSpecularColor * specularMultiplier, vec3(1.0));
    float gamma = 2.2;
    color = pow(color, vec3(1.0/gamma));
}