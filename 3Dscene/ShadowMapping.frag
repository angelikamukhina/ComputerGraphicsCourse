#version 330 core

// Interpolated values from the vertex shaders
in vec3 Normal_cameraspace;
in vec3 vertexPosition_cameraspace;
in vec3 Position_worldspace;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform mat4 M;
uniform mat4 V;
uniform vec3 MaterialDiffuseColor ;
uniform vec3 MaterialAmbientColor;
uniform vec3 MaterialSpecularColor;

const int lightsNumber = 2;
uniform vec3 LightPositions[lightsNumber];
uniform mat4 DepthBiasVPs[lightsNumber];
uniform sampler2DShadow shadowMaps[lightsNumber];

float shininess = 16.0;

void main(){
    vec3 normal = normalize(Normal_cameraspace);
    vec3 diffuseMultiplier = vec3(0);
    vec3 specularMultiplier = vec3(0);
    vec3 LightColor = vec3(1);
    float LightPower = 40.0f;

    for (int light = 0; light < lightsNumber; ++light) {
        vec3 LightPosition_worldspace = LightPositions[light];
        mat4 DepthBiasVP = DepthBiasVPs[light];

        // Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
        vec3 LightPosition_cameraspace = ( V * vec4(LightPosition_worldspace, 1)).xyz;
        vec3 LightDir_cameraspace = LightPosition_cameraspace - vertexPosition_cameraspace;

        float distance = length(LightDir_cameraspace);
        distance = distance * distance;
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
        float visibility = texture(shadowMaps[light], vec3(ShadowCoord.xy,  (ShadowCoord.z-bias)/ShadowCoord.w));
        diffuseMultiplier += visibility * lambertian * LightColor * LightPower / distance;
        specularMultiplier += visibility * specular * LightColor * LightPower / distance;
    }

	color = MaterialAmbientColor +
	    MaterialDiffuseColor * diffuseMultiplier + MaterialSpecularColor * specularMultiplier;
}