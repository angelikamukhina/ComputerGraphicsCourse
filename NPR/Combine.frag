#version 330 core
out vec3 FragColor;
in  vec2 TexCoords;
  
uniform sampler2D first;
uniform sampler2D second;
uniform sampler2D third;

uniform vec3 bgColor;
uniform vec3 fgColor;

void main() {
    float first_mask = texture(first, TexCoords).x;
    float second_mask = texture(second, TexCoords).x;
    float third_mask = texture(third, TexCoords).x;
    if (third_mask > 0) {
        FragColor = third_mask * fgColor;
    } else if (second_mask > 0) {
        FragColor = second_mask * bgColor;
    } else {
        FragColor = first_mask * fgColor;
    }
    float gamma = 2.2;
    FragColor = pow(FragColor, vec3(1.0/gamma));
}
