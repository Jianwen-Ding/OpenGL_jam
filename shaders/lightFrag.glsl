#version 410 core

in vec2 texCoord;
in vec3 v_normalVertex;
in vec3 fragPos;
in mat4 modelMat;

out vec4 FragColor;

uniform vec3 lightColor;

void main()
{
    FragColor = vec4(1.0f);
}