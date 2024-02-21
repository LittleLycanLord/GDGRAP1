#include "ModelObject.hpp"

using namespace models;

ModelObject::ModelObject(GLuint* shaderProg, glm::mat4* projection_matrix, glm::mat4* view_matrix, GLuint* texture) {
    this->modelMatrix = Matrix();
    this->shaderProg = *shaderProg;
    this->projection_matrix = *projection_matrix;
    this->view_matrix = *view_matrix;
    this->texture = *texture;
}

void ModelObject::updateModel(glm::mat4* view_matrix) {

    this->view_matrix = *view_matrix;

    unsigned int projectionLoc = glGetUniformLocation(this->shaderProg, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(this->projection_matrix));

    unsigned int transformLoc = glGetUniformLocation(this->shaderProg, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(*this->modelMatrix.getTransformMatrix()));

    unsigned int viewLoc = glGetUniformLocation(this->shaderProg, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(this->view_matrix));

    GLuint tex0Address = glGetUniformLocation(this->shaderProg, "tex0");
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glUniform1i(tex0Address, 0);
}

void ModelObject::drawModel(std::vector<GLuint>* mesh_indices) {
    glDrawElements(GL_TRIANGLES, mesh_indices->size(), GL_UNSIGNED_INT, 0);
}

Matrix* ModelObject::getMatrix() {
    return &this->modelMatrix;
}