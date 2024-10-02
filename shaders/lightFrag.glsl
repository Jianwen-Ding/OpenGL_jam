#version 410 core

in vec2 texCoord;
in vec3 v_vertexColors;

out vec4 FragColor;

uniform vec3 lightColor;

void main()
{
    FragColor = vec4(1.0f);
}