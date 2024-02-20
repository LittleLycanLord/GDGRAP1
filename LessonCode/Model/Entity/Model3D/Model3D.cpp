#include "Model3D.hpp"

using namespace models;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
Model3D::Model3D(string name, string modelPath)
    : Transformable(),
      modelName(name),
      modelPath(modelPath),
      texture(new Texture("NONE")) {}
Model3D::Model3D(string name, string modelPath, glm::vec3 position)
    : Transformable(position),
      modelName(name),
      modelPath(modelPath),
      texture(new Texture("NONE")) {}
Model3D::Model3D(string name, string modelPath, string texturePath)
    : Transformable(),
      modelName(name),
      modelPath(modelPath),
      texture(new Texture(texturePath)) {}
Model3D::Model3D(string name, string modelPath, string texturePath,
                 glm::vec3 position)
    : Transformable(position),
      modelName(name),
      modelPath(modelPath),
      texture(new Texture(texturePath)) {}
//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝
bool Model3D::checkIfLoaded() {
    if (tinyobj::LoadObj(&this->attributes, &this->shapes, &this->material,
                         &this->warning, &this->error,
                         this->modelPath.c_str())) {
        for (int i = 0; i < this->shapes[0].mesh.indices.size(); i++) {
            this->meshIndices.push_back(
                this->shapes[0].mesh.indices[i].vertex_index);
        }
    } else {
        return false;
    }
    cout << this->modelName + " has been loaded!" << endl;
    return true;
};
void Model3D::initializeModel() {
    glGenVertexArrays(1, &this->VAO);
    //* Open Vertex Array for Editing
    glBindVertexArray(this->VAO);

    if (this->VBOs.empty()) {
        GLuint VBO;
        this->VBOs.push_back(VBO);
    }
    for (GLuint VBO : this->VBOs) {
        glGenBuffers(1, &VBO);
        //* Load in the Vertices
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(GL_FLOAT) * this->getAttributes().vertices.size(),
                     this->getAttributes().vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    //* Define that we are using 3 dimensions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    if (this->EBOs.empty()) {
        GLuint EBO;
        this->EBOs.push_back(EBO);
    }
    for (GLuint EBO : this->EBOs) {
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(GLuint) * this->getMeshIndices().size(),
                     this->getMeshIndices().data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    this->texture->initializeTexture();
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    cout << this->modelName + " has been initialized!" << endl;
}
void Model3D::draw(GLuint shaderProgram) {
    //* Use the shader
    glUseProgram(shaderProgram);

    //* Load in the Vertex Array we made
    glBindVertexArray(this->getVAO());

    //* Use textures
    GLuint tex0Address = glGetUniformLocation(shaderProgram, "tex0");
    glBindTexture(GL_TEXTURE_2D, this->getTexture()->getTexture());
    glUniform1i(tex0Address, 0);
    glDrawElements(
        GL_TRIANGLES, GLsizei(this->meshIndices.size()), GL_UNSIGNED_INT,
        0);  // the GLsizei() is just to remove
             // a warning, since glDrawElements has a parameter of it, and
             // it wants us to make sure we only plug GLsizei's in it.
}
void Model3D::cleanUp() {
    this->texture->cleanUp();
    glDeleteVertexArrays(1, &this->VAO);
    for (GLuint VBO : this->VBOs) glDeleteBuffers(1, &VBO);
    for (GLuint EBO : this->EBOs) glDeleteBuffers(1, &EBO);
    cout << this->modelName + " has been cleaned up!" << endl;
}
//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
string Model3D::getModelName() { return this->modelName; }
string Model3D::getModelPath() { return this->modelPath; }
vector<tinyobj::shape_t> Model3D::getShapes() { return this->shapes; }
vector<tinyobj::material_t> Model3D::getMaterial() { return this->material; }
string Model3D::getWarning() { return this->warning; }
string Model3D::getError() { return this->error; }
tinyobj::attrib_t Model3D::getAttributes() { return this->attributes; }
GLuint Model3D::getVAO() { return this->VAO; }
vector<GLuint> Model3D::getMeshIndices() { return this->meshIndices; }
vector<GLuint> Model3D::getVBOs() { return this->VBOs; }
vector<GLuint> Model3D::getEBOs() { return this->EBOs; }
Texture* Model3D::getTexture() { return this->texture; }
// namespace models
