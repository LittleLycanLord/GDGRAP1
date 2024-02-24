#include "Shaders.hpp"

using namespace shaders;

Shaders::Shaders() {
    this->shaderProg = GLuint();
    this->texture = GLuint();
}

void Shaders::initializeShaders() {
    std::fstream vertSrc("Shaders/sample.vert");
    std::stringstream vertBuff;
    vertBuff << vertSrc.rdbuf();

    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    std::fstream fragSrc("Shaders/sample.frag");
    std::stringstream fragBuff;
    fragBuff << fragSrc.rdbuf();

    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &v, NULL);
    glCompileShader(vertexShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &f, NULL);
    glCompileShader(fragShader);

    this->shaderProg = glCreateProgram();
    glAttachShader(this->shaderProg, vertexShader);
    glAttachShader(this->shaderProg, fragShader);

    glLinkProgram(this->shaderProg);

    glGenTextures(1, &this->texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture);
}

void Shaders::assignTexture(int colorChannels, int img_width, int img_height,
                            unsigned char* tex_bytes) {
    switch (colorChannels) {
        case 3:
            glTexImage2D(GL_TEXTURE_2D, 0,  //? <- Texture Index
                         GL_RGB, img_width, img_height, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, tex_bytes);
            break;
        case 4:
            glTexImage2D(GL_TEXTURE_2D, 0,  //? <- Texture Index
                         GL_RGBA, img_width, img_height, 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, tex_bytes);
            break;
    }
    glGenerateMipmap(GL_TEXTURE_2D);
}

GLuint* Shaders::getShaderProgram() {
    return &this->shaderProg;
}

GLuint* Shaders::getTexture() {
    return &this->texture;
}