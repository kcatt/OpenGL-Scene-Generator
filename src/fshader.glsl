#version 330 core

in vec3 fragNormal;
in vec3 fragPos;

struct Light
{
    vec3 position;
    vec3 color;
    vec3 ambient;
};

struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emissive;
    float shininess;
};

uniform vec3     viewPos;
uniform Light    light;
uniform Material material;

out vec4 color;

void main()
{
    // Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = material.ambient * light.color;
  	
    // Diffuse 
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.color * (diff * material.diffuse);
    
    // Specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.color * (spec * material.specular);  
    
    // Scene color
    vec3 sceneColor = material.emissive + material.ambient * light.ambient;

    vec3 result = (sceneColor + ambient + diffuse + specular);
    color = vec4(result, 1.0f);
}