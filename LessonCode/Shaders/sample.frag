#version 330 core

out vec4 FragColor;
uniform sampler2D tex0;
in vec3 normCoord;
in vec2 texCoord;
in vec3 fragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform float ambientStr;
uniform vec3 ambientColor;

uniform vec3 cameraPos;
uniform float specStr;
uniform float specPhong;

void main() {
    vec3 normal = normalize(normCoord);
    vec3 lightDir = normalize(lightPos - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 ambientCol = ambientStr * ambientColor;

    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(reflectDir, viewDir), 0.1), specPhong);
    vec3 specColor = spec * specStr * lightColor;

    //FragColor = vec4(0.37f, 0.56f, 0.92f, 1.0f);
    //                       - Use Lighting -                     - Use Texture -
    FragColor = vec4(specColor + diffuse + ambientCol, 1.0) * texture(tex0, texCoord);
}