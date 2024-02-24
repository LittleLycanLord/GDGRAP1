#include "Matrix.hpp"

using namespace matrix;

Matrix::Matrix() { this->initializeTransformMatrix(); }

void Matrix::initializeTransformMatrix() {
    this->fTranslate_X          = 0.0f;
    this->fTranslate_Y          = 0.0f;
    this->fTranslate_Z          = -2.0f;

    this->fScale_X              = 0.95f;
    this->fScale_Y              = 0.95f;
    this->fScale_Z              = 0.95f;

    this->vecTheta              = glm::vec3(0.f);
    this->vecRotationAxis_X     = glm::vec3(1.0f, 0.0f, 0.0f);
    this->vecRotationAxis_Y     = glm::vec3(0.0f, 1.0f, 0.0f);
    this->vecRotationAxis_Z     = glm::vec3(0.0f, 0.0f, 1.0f);

    this->fPerspectiveTheta     = 60.0f;
    this->transformation_matrix = glm::mat4(1.0f);
}

void Matrix::calculateTransformMatrix() {
    glm::mat4 identity_matrix   = glm::mat4(1.0f);

    this->transformation_matrix = glm::translate(
        identity_matrix,
        glm::vec3(this->fTranslate_X, this->fTranslate_Y, this->fTranslate_Z));

    this->transformation_matrix =
        glm::scale(this->transformation_matrix,
                   glm::vec3(this->fScale_X, this->fScale_Y, this->fScale_Z));

    this->transformation_matrix =
        glm::rotate(this->transformation_matrix, glm::radians(this->vecTheta.x),
                    glm::normalize(this->vecRotationAxis_X));
    this->transformation_matrix =
        glm::rotate(this->transformation_matrix, glm::radians(this->vecTheta.y),
                    glm::normalize(this->vecRotationAxis_Y));
    this->transformation_matrix =
        glm::rotate(this->transformation_matrix, glm::radians(this->vecTheta.z),
                    glm::normalize(this->vecRotationAxis_Z));
}

void Matrix::setTranslateVar(char cVar, float fValue) {
    switch (cVar) {
        case 'X':
            this->fTranslate_X = fValue;
            break;
        case 'Y':
            this->fTranslate_Y = fValue;
            break;
        case 'Z':
            this->fTranslate_Z = fValue;
            break;
    }
}

float Matrix::getTranslateVar(char cVar) {
    switch (cVar) {
        case 'X':
            return this->fTranslate_X;
        case 'Y':
            return this->fTranslate_Y;
        case 'Z':
            return this->fTranslate_Z;
    }

    return 0.0f;
}

void Matrix::setScaleVar(char cVar, float fValue) {
    switch (cVar) {
        case 'X':
            this->fScale_X = fValue;
            break;
        case 'Y':
            this->fScale_Y = fValue;
            break;
        case 'Z':
            this->fScale_Z = fValue;
            break;
    }
}

float Matrix::getScaleVar(char cVar) {
    switch (cVar) {
        case 'X':
            return this->fScale_X;
        case 'Y':
            return this->fScale_Y;
        case 'Z':
            return this->fScale_Z;
    }

    return 0.0f;
}

void Matrix::setRotateVar(char cVar, float fValue) {
    switch (cVar) {
        case 'X':
            this->vecTheta.x = fValue;
            break;
        case 'Y':
            this->vecTheta.y = fValue;
            break;
        case 'Z':
            this->vecTheta.z = fValue;
            break;
    } 
}

float Matrix::getRotateVar(char cVar) {
    switch (cVar) {
        case 'X':
            return this->vecTheta.x;
        case 'Y':
            return this->vecTheta.y;
        case 'Z':
            return this->vecTheta.z;
    }

    return 0.0f;
}

float Matrix::getPerspectiveTheta() { return this->fPerspectiveTheta; }

void Matrix::setTransformMatrix(glm::mat4 value) {
    this->transformation_matrix = value;
}

glm::mat4* Matrix::getTransformMatrix() { return &this->transformation_matrix; }
