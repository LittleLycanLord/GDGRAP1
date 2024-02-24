#include "ModelObject.hpp"

using namespace models;

ModelObject::ModelObject() {
    this->modelMatrix = Matrix();
    this->projection_matrix = glm::perspective(glm::radians(60.f), 600.f / 600.f, 0.1f, 100.f);
    this->view_matrix = glm::mat4(1.0f);
    this->shaderProg = GLuint();
    this->texture = GLuint();
    this->isInitialized = false;
}

void ModelObject::initialize(GLuint* shaderProg, glm::mat4* view_matrix, GLuint* texture) {
    this->shaderProg = *shaderProg;
    this->view_matrix = *view_matrix;
    this->texture = *texture;
}

void ModelObject::updateModel() {

    this->modelMatrix.calculateTransformMatrix();
   
    unsigned int projectionLoc = glGetUniformLocation(this->shaderProg, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(this->projection_matrix));

    unsigned int transformLoc = glGetUniformLocation(this->shaderProg, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(*this->modelMatrix.getTransformMatrix()));

    GLuint tex0Address = glGetUniformLocation(this->shaderProg, "tex0");
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glUniform1i(tex0Address, 0);
}

void ModelObject::setModelInFrontOfCam(glm::vec3* cameraPosition, glm::vec3* centerPosition) {
    float fOffset = 0.f;
    glm::vec3 Front = glm::vec3(*centerPosition + *cameraPosition);
    //Front = glm::normalize(Front);

   /* this->modelMatrix.setTranslateVar('X', cameraPosition->x + centerPosition->x);
    this->modelMatrix.setTranslateVar('Y', cameraPosition->y + +centerPosition->y);
    this->modelMatrix.setTranslateVar('Z', (cameraPosition->z + +centerPosition->z) - fOffset);*/

    this->modelMatrix.setTranslateVar('X', Front.x);
    this->modelMatrix.setTranslateVar('Y', Front.y);
    this->modelMatrix.setTranslateVar('Z', Front.z);
}   

void ModelObject::drawModel(std::vector<GLuint>* mesh_indices) {
    this->updateModel();
    glDrawElements(GL_TRIANGLES, mesh_indices->size(), GL_UNSIGNED_INT, 0);
}

void ModelObject::setViewMatrix(glm::mat4 viewMatrix) {
    this->view_matrix = viewMatrix;
}

Matrix* ModelObject::getMatrix() {
    return &this->modelMatrix;
}