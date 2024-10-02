#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 u_viewMat;
uniform mat4 u_perspectiveMat;
uniform mat4 u_modelMat;
uniform mat4 u_rotationInverseQuat;

out vec3 v_vertexColors;
out vec2 texCoord;
void main()
{
    texCoord = aTexCoord;
    v_vertexColors = color;
    vec4 newPos = u_perspectiveMat *  u_viewMat * u_modelMat * vec4(position,1.0f);
    gl_Position = newPos;
}