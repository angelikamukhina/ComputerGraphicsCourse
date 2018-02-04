#version 330 core

in vec3 v_barycentric; // barycentric coordinate inside the triangle
uniform float f_thickness; // thickness of the rendered lines.

layout(location = 0) out vec3 color;

// http://codeflow.org/entries/2012/aug/02/easy-wireframe-display-with-barycentric-coordinates/
float edgeFactor(){
    vec3 d = fwidth(v_barycentric);
    vec3 a3 = smoothstep(vec3(0.0), d * f_thickness, v_barycentric);
    return min(min(a3.x, a3.y), a3.z);
}

void main(){
    float mask = mix(1, 0, edgeFactor());
    color = vec3(mask);
}
