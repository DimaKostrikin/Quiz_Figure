#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;


uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

// in vec3 ourColor;
// in vec2 TexCoord;

// uniform sampler2D texture1;
// uniform sampler2D texture2;

void main()
{
//     FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
//     FragColor = vec4(lightColor * objectColor, 1.0);

//     vec3 norm = normalize(Normal);
//     vec3 lightDir = normalize(lightPos - FragPos);
//     float diff = max(dot(norm, lightDir), 0.0);
//     vec3 diffuse = diff * lightColor;
//
//     float specularStrength = 0.5;
//     vec3 viewDir = normalize(viewPos - FragPos);
//     vec3 reflectDir = reflect(-lightDir, norm);
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
//     vec3 specular = specularStrength * spec * lightColor;
//
//     float ambientStrength = 0.9;
//     vec3 ambient = ambientStrength * lightColor;
//
//     vec3 result = (ambient + diffuse + specular) * objectColor;
//     FragColor = vec4(result, 1.0);

    // Фоновая состовляющая
//     vec3 ambient = lightColor * material.ambient;
    vec3 ambient = light.ambient * material.ambient;

    // Составляющая рассеивания
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
//     vec3 diffuse = lightColor * (diff * material.diffuse);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    // Составляющая отражения
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//     vec3 specular = lightColor * (spec * material.specular);
    vec3 specular = light.specular * (spec * material.specular);

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);

}