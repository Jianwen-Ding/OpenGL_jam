#version 410 core

in vec3 TexCoords; // direction vector representing a 3D texture coordinate
uniform samplerCube u_cubemap; // cubemap texture sampler

out vec4 FragColor;

void main()
{             
    FragColor = texture(u_cubemap, TexCoords);
}  