#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "fstream"
#include "sstream"

namespace shaders {
	class Shaders {
	private:
		GLuint shaderProg;
		GLuint texture;
	public:
		Shaders();
	public:
		void initializeShaders();
	public:
		void assignTexture(int img_width, int img_height, unsigned char* tex_bytes);
	public:
		GLuint* getShaderProgram();
		GLuint* getTexture();
	};
}

/* fstream vertSrc("Shaders/sample.vert");
    fstream fragSrc("Shaders/sample.frag");
    stringstream vertBuff;
    stringstream fragBuff;
    //* Add the file stream to the string stream
    vertBuff << vertSrc.rdbuf();
    fragBuff << fragSrc.rdbuf();
    //* Convert the stream to a char array
    string vertS          = vertBuff.str();
    string fragS          = fragBuff.str();
    const char* v         = vertS.c_str();
    const char* f         = fragS.c_str();
    GLuint vertexShader   = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, &v, NULL);
    glShaderSource(fragmentShader, 1, &f, NULL);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    //* Create a shader program, then attached the shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    //* Link the shader program
    glLinkProgram(shaderProgram);*/