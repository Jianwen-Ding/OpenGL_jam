#version 410 core

in vec2 texCoord;
in vec3 v_vertexColors;

out vec4 FragColor;

uniform sampler2D u_givenTexture1;
uniform sampler2D u_givenTexture2;
uniform float u_ambienceStrength;
uniform vec3 u_lightColor;

void main()
{
    vec3 lightCol = u_lightColor;
    vec3 ambienceCol = lightCol * u_ambienceStrength;
    vec3 lightResult = lightCol * ambienceCol;
    FragColor = mix(texture(u_givenTexture1, texCoord),texture(u_givenTexture2, texCoord),0.2f) * vec4(lightResult, 1.0f);
}