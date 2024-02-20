#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "iostream"
#include "string"
#include "vector"
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "../../../stb_image.h"

using namespace std;

namespace models {
class Texture {
    //* ╔════════════╗
    //* ║ Attributes ║
    //* ╚════════════╝
private:
    //* Texture Attributes
    string path;
    vector<GLfloat> UVData;
    int imageWidth;
    int imageHeight;
    int colorChannels;
    GLuint VBO_UV;
    GLuint texture;

    //* ╔═══════════════════════════════╗
    //* ║ Constructors & Deconstructors ║
    //* ╚═══════════════════════════════╝
public:
    Texture(string path);
    //* ╔═════════╗
    //* ║ Methods ║
    //* ╚═════════╝
public:
    void initializeTexture();
    void cleanUp();

private:
    bool checkIfLoaded();
    //* ╔═══════════════════╗
    //* ║ Getters & Setters ║
    //* ╚═══════════════════╝
public:
    GLuint getVBO_UV();
    GLuint getTexture();
    void setUVData(vector<GLfloat> UVData);
};
}  // namespace models