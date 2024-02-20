#include "Texture.hpp"

using namespace models;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
Texture::Texture(string path) { this->path = path; };
//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝
void Texture::initializeTexture() {
    if (!this->checkIfLoaded()) {
        cout << "Texture Failed to Load : " << this->path << endl;
    } else {
        stbi_set_flip_vertically_on_load(true);

        //* Load Texture
        unsigned char* tex_bytes =
            stbi_load(this->path.c_str(), &this->imageWidth, &this->imageHeight,
                      &this->colorChannels, 0);
        //* Create an OpenGL reference for the texture
        glGenTextures(1, &this->texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->texture);
        //* Assign a texture to that reference
        switch (colorChannels) {
            case 3:
                glTexImage2D(GL_TEXTURE_2D, 0,  //? <- Texture Index
                             GL_RGB, imageWidth, imageHeight, 0, GL_RGB,
                             GL_UNSIGNED_BYTE, tex_bytes);
                break;
            case 4:
                glTexImage2D(GL_TEXTURE_2D, 0,  //? <- Texture Index
                             GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA,
                             GL_UNSIGNED_BYTE, tex_bytes);
                break;
        }
        //* Generate mipmaps
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(tex_bytes);

        //* Generate Buffers
        glGenBuffers(1, &this->VBO_UV);
        //* Bind UV Buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO_UV);
        //* Load UV Data
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->UVData.size(),
                     &this->UVData[0], GL_DYNAMIC_DRAW);
        //*
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                              (void*)0);
        glEnableVertexAttribArray(2);
    }
}

bool Texture::checkIfLoaded() {
    if (stbi_load(this->path.c_str(), &this->imageWidth, &this->imageHeight,
                  &this->colorChannels, 0)) {
        return true;
    }
    return false;
}

void Texture::cleanUp() { glDeleteBuffers(1, &this->VBO_UV); }
//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
GLuint Texture::getVBO_UV() { return this->VBO_UV; }
GLuint Texture::getTexture() { return this->texture; }
void Texture::setUVData(vector<GLfloat> UVData) { this->UVData = UVData; }
// namespace models
