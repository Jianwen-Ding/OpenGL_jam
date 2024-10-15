#version 410 core

in vec2 texCoord;
in vec3 v_vertexColors;

out vec4 FragColor;

uniform sampler2DArray u_givenTextures;
uniform float u_ambienceStrength;
uniform vec3 u_lightColor;

# define MAX_TEXTURES 100

uniform vec2 u_uvCoords[MAX_TEXTURES];
uniform int u_textureLength;
void main()
{
    vec3 lightCol = u_lightColor;
    vec3 ambienceCol = lightCol * u_ambienceStrength;
    vec3 lightResult = lightCol * ambienceCol;
    vec2 adjustTexCoords[MAX_TEXTURES];
    for(int i = 0 ; i < u_textureLength; i++){
        vec2 final = (u_uvCoords[i] * (texCoord - floor(texCoord))) + floor(texCoord);
        adjustTexCoords[i] = final;
    }
    
   FragColor = mix(texture(u_givenTextures, vec3(adjustTexCoords[0],0)),texture(u_givenTextures, vec3(adjustTexCoords[1],1)),0.5f) * vec4(lightResult, 1.0f);
   //FragColor = texture(u_givenTextures, vec3(texCoord * u_uvCoords[0],0));
}