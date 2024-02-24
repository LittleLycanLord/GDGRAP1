#pragma once

#include "../../Component/Matrix.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "iostream"
#include "vector"

namespace models {
using namespace matrix;
class ModelObject {
private:
    Matrix modelMatrix;

private:
    glm::mat4 projection_matrix;
    glm::mat4 view_matrix;

private:
    GLuint shaderProg;
    GLuint texture;

private:
    bool isInitialized;

public:
    ModelObject();

public:
    void initialize(GLuint* shaderProg, glm::mat4* view_matrix,
                    GLuint* texture);
    void updateModel(glm::vec3 cameraPosition);
    void setModelInFrontOfCam(glm::vec3* cameraPosition,
                              glm::vec3* centerPosition,
                              glm::vec3* cameraTheta);
    void drawModel(std::vector<GLuint>* mesh_indices,
                   std::vector<GLfloat>* fullVertexData,
                   glm::vec3 cameraPosition);

public:
    void setViewMatrix(glm::mat4 viewMatrix);
    Matrix* getMatrix();
};
}  // namespace models