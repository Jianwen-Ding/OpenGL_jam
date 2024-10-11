#version 410 core

in vec2 texCoord;
in vec3 v_vertexColors;

out vec4 FragColor;

uniform sampler2DArray u_givenTextures;
uniform float u_ambienceStrength;
uniform vec3 u_lightColor;

void main()
{
    vec3 lightCol = u_lightColor;
    vec3 ambienceCol = lightCol * u_ambienceStrength;
    vec3 lightResult = lightCol * ambienceCol;
    FragColor = mix(texture(u_givenTextures, vec3(texCoord,0)),texture(u_givenTextures, vec3(texCoord,1)),1.0f) * vec4(lightResult, 1.0f);
}