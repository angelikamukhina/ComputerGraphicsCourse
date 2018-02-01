// fragment shader
#version 330 core
out vec3 FragColor;
in  vec2 TexCoords;
  
uniform sampler2D fboAttachment;
  
void main()
{
    vec3 color = texture(fboAttachment, TexCoords).rgb;
    float gamma = 2.2;
    FragColor = pow(color, vec3(1.0/gamma));
} 