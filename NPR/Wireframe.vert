#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace; // position of the vertices
layout(location = 1) in vec3 v_bc;  // barycentric coordinate inside the triangle

out vec3 v_barycentric; // barycentric coordinate inside the triangle

uniform mat4 MVP;

void main() {
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
	v_barycentric = v_bc;
}
