#version 330 core

#define NR_POINT_LIGHTS 4

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

struct Material {
    sampler2D texture_diffuse1;
    sampler2D specular;
    float shininess;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirLightLamp {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
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

// uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirLightLamp dirLightLamp;
// uniform SpotLight spotLight;
uniform Material material;

uniform vec3 viewPos;

vec3 CalcDirLight(DirLightLamp light, vec3 normal, vec3 viewDir);
// vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
// vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    // Свойства
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Этап №1: Направленное освещение
    vec3 result = CalcDirLight(dirLightLamp, norm, viewDir);


    // Этап №2: Точечные источники света
//     for(int i = 0; i < NR_POINT_LIGHTS; i++)
//         result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);

    // Этап №3: Прожектор
//     result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLightLamp light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // Рассеянное затенение
    float diff = max(dot(normal, lightDir), 0.0);

    // Отраженное затенение
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // Комбинируем результаты
    vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
    return (ambient + diffuse + specular);

}

// vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
// {
//     vec3 lightDir = normalize(light.position - fragPos);
//
//     // Рассеянное затенение
//     float diff = max(dot(normal, lightDir), 0.0);
//
//
//
//     // Отраженное затенение
//     vec3 reflectDir = reflect(-lightDir, normal);
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//
//     // Затухание
//     float distance = length(light.position - fragPos);
//     float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
//
//     // Комбинируем результаты
//     vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoord));
// //     vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoord));
//     vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoord));
//
//     vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
//     ambient *= attenuation;
//     diffuse *= attenuation;
//     specular *= attenuation;
//     return (ambient + diffuse + specular);
//
// }
//
// vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
// {
//     vec3 lightDir = normalize(light.position - fragPos);
//     // diffuse shading (диффузное затенение)
//     float diff = max(dot(normal, lightDir), 0.0);
//     // specular shading (отраженное затенение)
//     vec3 reflectDir = reflect(-lightDir, normal);
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//     // attenuation (затухание)
//     float distance = length(light.position - fragPos);
// //     float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
//     float attenuation = 0.4 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
//
//     // интенсивность прожектора
//     float theta = dot(lightDir, normalize(-light.direction));
//     float epsilon = light.cutOff - light.outerCutOff;
//     float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
//     // совмещаем результаты
//     vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoord));
//     vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoord));
//     vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
//     ambient *= attenuation * intensity;
//     diffuse *= attenuation * intensity;
//     specular *= attenuation * intensity;
//     return (ambient + diffuse + specular);
//
// }