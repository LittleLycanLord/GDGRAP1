#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 vertexNormal;
out vec3 normCoord;
layout(location = 2) in vec2 aTex;
out vec2 texCoord;

out vec3 fragPos;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main() {
    normCoord = mat3(transpose(inverse(transform))) * vertexNormal;

    texCoord = aTex;

    fragPos = vec3(transform * vec4(aPos, 1.0f));
    gl_Position = projection * view * transform * vec4(aPos, 1.0);

}