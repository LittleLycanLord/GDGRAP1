#include "ModelObject.hpp"

using namespace models;

//* - - - - - LIGHTING - - - - -
glm::vec3 lightPos     = glm::vec3(-10, 3, 0);
glm::vec3 lightColor   = glm::vec3(1, 1, 1);
float ambientStrength  = 0.5f;
glm::vec3 ambientColor = lightColor;
float specStrength     = 0.5f;
float specPhong        = 16;  //? Usually 16 - 25
//* - - - - - END OF LIGHTING - - - - -

ModelObject::ModelObject() {
    this->modelMatrix = Matrix();
    this->projection_matrix =
        glm::perspective(glm::radians(60.f), 600.f / 600.f, 0.1f, 100.f);
    this->view_matrix   = glm::mat4(1.0f);
    this->shaderProg    = GLuint();
    this->texture       = GLuint();
    this->isInitialized = false;
}

void ModelObject::initialize(GLuint* shaderProg, glm::mat4* view_matrix,
                             GLuint* texture) {
    this->shaderProg  = *shaderProg;
    this->view_matrix = *view_matrix;
    this->texture     = *texture;
}

void ModelObject::updateModel(glm::vec3 cameraPosition) {
    this->modelMatrix.calculateTransformMatrix();

    unsigned int projectionLoc =
        glGetUniformLocation(this->shaderProg, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
                       glm::value_ptr(this->projection_matrix));

    unsigned int transformLoc =
        glGetUniformLocation(this->shaderProg, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
                       glm::value_ptr(*this->modelMatrix.getTransformMatrix()));

    GLuint tex0Address = glGetUniformLocation(this->shaderProg, "tex0");
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glUniform1i(tex0Address, 0);

    //* Use lighting
    GLuint lightAddress = glGetUniformLocation(this->shaderProg, "lightPos");
    glUniform3fv(lightAddress, 1, glm::value_ptr(lightPos));

    GLuint lightColorAddress =
        glGetUniformLocation(this->shaderProg, "lightColor");
    glUniform3fv(lightColorAddress, 1, glm::value_ptr(lightColor));

    GLuint ambientAddress = glGetUniformLocation(this->shaderProg, "ambientStr");
    glUniform1f(ambientAddress, ambientStrength);

    GLuint ambientColorAddress =
        glGetUniformLocation(this->shaderProg, "ambientColor");
    glUniform3fv(ambientColorAddress, 1, glm::value_ptr(ambientColor));

    GLuint cameraPosAddress = glGetUniformLocation(this->shaderProg, "cameraPos");
    glUniform3fv(cameraPosAddress, 1, glm::value_ptr(cameraPosition));

    GLuint specStrAddress = glGetUniformLocation(this->shaderProg, "specStr");
    glUniform1f(specStrAddress, specStrength);

    GLuint specPhongAddress = glGetUniformLocation(this->shaderProg, "specPhong");
    glUniform1f(specPhongAddress, specPhong);
}

void ModelObject::setModelInFrontOfCam(glm::vec3* cameraPosition,
                                       glm::vec3* centerPosition,
                                       glm::vec3* cameraTheta) {
    float offset    = 5.f;
    glm::vec3 Front = (*cameraPosition) + offset * (*centerPosition);

    this->modelMatrix.setTranslateVar('X', Front.x);
    this->modelMatrix.setTranslateVar('Y', Front.y);
    this->modelMatrix.setTranslateVar('Z', Front.z);

    glm::vec3 Facing = -*cameraTheta;

    this->modelMatrix.setRotateVar('X', Facing.x);
    this->modelMatrix.setRotateVar('Y', Facing.y);
    this->modelMatrix.setRotateVar('Z', Facing.z);
}

void ModelObject::drawModel(std::vector<GLuint>* mesh_indices,
                            std::vector<GLfloat>* fullVertexData,
                                glm::vec3 cameraPosition) {
    this->updateModel(cameraPosition);
    // glDrawElements(GL_TRIANGLES, GLsizei(mesh_indices->size()), GL_UNSIGNED_INT,
    //                0);
    glDrawArrays(GL_TRIANGLES, 0, GLsizei(fullVertexData->size()) / 8);
}

void ModelObject::setViewMatrix(glm::mat4 viewMatrix) {
    this->view_matrix = viewMatrix;
}

Matrix* ModelObject::getMatrix() { return &this->modelMatrix; }