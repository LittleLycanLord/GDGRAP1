#pragma once
#include "../../Component/Transformable.hpp"
#include "../Texture/Texture.hpp"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "iostream"
#include "string"
#include "vector"
// #define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

using namespace std;

namespace models {
using namespace components;
class Model3D : public Transformable {
    //* ╔════════════╗
    //* ║ Attributes ║
    //* ╚════════════╝
public:
    //* Model Attributes
    string modelName;
    string modelPath;
    vector<tinyobj::shape_t> shapes;
    vector<tinyobj::material_t> material;
    string warning, error;
    tinyobj::attrib_t attributes;
    vector<GLuint> meshIndices;

    //* Model Objects
public:
    GLuint VAO;           //? Vertex Array
    vector<GLuint> VBOs;  //? Vertex Buffer
    vector<GLuint> EBOs;

    Texture* texture;
    //* ╔═══════════════════════════════╗
    //* ║ Constructors & Deconstructors ║
    //* ╚═══════════════════════════════╝
public:
    Model3D(string name, string modelPath);
    Model3D(string name, string modelPath, glm::vec3 position);
    Model3D(string name, string modelPath, string texturePath);
    Model3D(string name, string modelPath, string texturePath,
            glm::vec3 position);
    //* ╔═════════╗
    //* ║ Methods ║
    //* ╚═════════╝
public:
    bool checkIfLoaded();
    void initializeModel();
    void draw(GLuint shaderProgram);
    void cleanUp();
    //* ╔═══════════════════╗
    //* ║ Getters & Setters ║
    //* ╚═══════════════════╝
public:
    string getModelName();
    string getModelPath();
    vector<tinyobj::shape_t> getShapes();
    vector<tinyobj::material_t> getMaterial();
    string getWarning();
    string getError();
    tinyobj::attrib_t getAttributes();

    GLuint getVAO();
    vector<GLuint> getMeshIndices();
    vector<GLuint> getVBOs();
    vector<GLuint> getEBOs();
    Texture* getTexture();
};
}  // namespace models