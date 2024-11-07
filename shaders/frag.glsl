#version 410 core

in vec2 texCoord;
in vec3 v_normalVertex;
in vec3 fragPos;
in mat4 modelMat;

out vec4 FragColor;

struct DirLight{
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

# define DEFAULT_SPEC vec3(0.15)
# define MAX_LIGHTS 25

uniform int u_specBarrier;
uniform int u_dirLightLength;
uniform DirLight u_dirLight[MAX_LIGHTS];
uniform int u_pointLightLength;
uniform PointLight u_pointLight[MAX_LIGHTS];
// TODO: Implement later
uniform int u_spotLightLength;
uniform SpotLight u_spotLight[MAX_LIGHTS];
uniform vec3 u_viewPos;


# define MAX_TEXTURES 32
uniform sampler2DArray u_givenTextures;
uniform vec2 u_uvCoords[MAX_TEXTURES];
uniform int u_textureLength;

vec3 generateDirResult(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseTex, vec3 specTex);

vec3 generatePointResult(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseTex, vec3 specTex);

vec3 generateSpotResult(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseTex, vec3 specTex);

void main()
{
    
    // Deals with adjusting texture coordinates to uv
    vec2 adjustTexCoords[MAX_TEXTURES];
    for(int i = 0 ; i < u_textureLength; i++){
        vec2 final = (u_uvCoords[i] * (texCoord - floor(texCoord))) + floor(texCoord);
        adjustTexCoords[i] = final;
    }

    vec3 specularTex;
    if(u_textureLength != u_specBarrier){
        specularTex = vec3(texture(u_givenTextures, vec3(adjustTexCoords[u_specBarrier],u_specBarrier)));
    }
    else{
        specularTex = DEFAULT_SPEC;
    }

    vec3 diffuseTex = vec3(texture(u_givenTextures, vec3(adjustTexCoords[0],0)));

    vec3 norm = normalize(v_normalVertex);
    // Normal adjusted to transform
    vec3 adjustNorm = mat3(transpose(inverse(modelMat))) * norm;
    vec3 viewDir = normalize(u_viewPos - fragPos);

    vec3 lightResult = vec3(0.0f);
    for(int i = 0; i < u_dirLightLength; i++){
        lightResult += generateDirResult(u_dirLight[i], adjustNorm, viewDir, diffuseTex, specularTex);
    }
    for(int i = 0; i < u_pointLightLength; i++){
        lightResult += generatePointResult(u_pointLight[i], adjustNorm, fragPos, viewDir, diffuseTex, specularTex);
    }
    for(int i = 0; i < u_spotLightLength; i++){
        lightResult += generateSpotResult(u_spotLight[i], adjustNorm, fragPos, viewDir, diffuseTex, specularTex);
    }

    // Compiling final result
    FragColor = vec4(lightResult,1.0f);
   //FragColor = texture(u_givenTextures, vec3(texCoord * u_uvCoords[0],0));
}

vec3 generateDirResult(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseTex, vec3 specTex){
    vec3 lightDir = normalize(-light.direction);

    // Ambient
    vec3 ambient = light.ambient * diffuseTex;

    // Diffusion
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * diffuseTex;
    
    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    vec3 specular = light.specular * spec * specTex;

    return  (ambient + diffuse + specular);
}

vec3 generatePointResult(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseTex, vec3 specTex) {
    vec3 lightDir = normalize(light.position - fragPos);

    // Ambient
    vec3 ambient = light.ambient * diffuseTex;

    // Diffusion
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * diffuseTex;

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    vec3 specular = light.specular * spec * specTex;

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return  (ambient + diffuse + specular);
}

vec3 generateSpotResult(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseTex, vec3 specTex){
    vec3 lightDir = normalize(light.position - fragPos);

    // Ambient
    vec3 ambient = light.ambient * diffuseTex;

    // Diffusion
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * diffuseTex;

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    vec3 specular = light.specular * spec * specTex;

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return ambient + diffuse + specular;
}