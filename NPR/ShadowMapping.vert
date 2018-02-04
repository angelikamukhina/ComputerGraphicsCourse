#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;

// Output data ; will be interpolated for each fragment.
out vec3 Normal_cameraspace;
out vec3 vertexPosition_cameraspace;
out vec3 Position_worldspace;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;

void main(){
	gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);

	vec4 vertPos4 = M * vec4(vertexPosition_modelspace, 1);
	Position_worldspace = vertPos4.xyz / vertPos4.w;
	vertexPosition_cameraspace = ( V * M * vec4(vertexPosition_modelspace, 1)).xyz;

	Normal_cameraspace = ( V * M * vec4(vertexNormal_modelspace, 0)).xyz;
}

