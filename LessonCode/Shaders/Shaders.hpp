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
        void assignTexture(int colorChannels, int img_width, int img_height,
                           unsigned char* tex_bytes);

    public:
		GLuint* getShaderProgram();
		GLuint* getTexture();
	};
}

