#version 410 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 u_perspectiveMat;
// Needs to be processed without considering position
uniform mat4 u_viewMat;

void main()
{
    TexCoords = aPos;
    gl_Position = u_perspectiveMat * u_viewMat * vec4(aPos, 1.0);
}  