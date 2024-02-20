#version 330 core

out vec4 FragColor;
uniform sampler2D tex0;
in vec2 texCoord;

void main() {
    //FragColor = vec4(0.37f, 0.56f, 0.92f, 1.0f);
    FragColor = texture(tex0, texCoord);
}