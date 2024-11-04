#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 u_viewMat;
uniform mat4 u_perspectiveMat;
uniform mat4 u_modelMat;
uniform mat4 u_rotationInverseQuat;

out vec3 v_normalVertex;
out vec3 fragPos;
out vec2 texCoord;
out mat4 modelMat;
void main()
{
    modelMat = u_modelMat;
    texCoord = aTexCoord;
    v_normalVertex = normals;
    fragPos = vec3(u_modelMat * vec4(position,1.0f));
    vec4 newPos = u_perspectiveMat *  u_viewMat * u_modelMat * vec4(position,1.0f);
    gl_Position = newPos;
}