#include "Transformable.hpp"

using namespace components;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
Transformable::Transformable() {
    this->positionVector = glm::vec3(0.0f, 0.0f, 0.0f);
    this->scaleVector    = glm::vec3(1.0f, 1.0f, 1.0f);
    this->thetaVector    = glm::vec3(0.0f, 0.0f, 0.0f);
}
Transformable::Transformable(glm::vec3 position) {
    this->positionVector = position;
    this->scaleVector    = glm::vec3(1.0f, 1.0f, 1.0f);
    this->thetaVector    = glm::vec3(0.0f, 0.0f, 0.0f);
}
Transformable::~Transformable() {}
//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝
void Transformable::translate(glm::vec3 amount) {
    this->positionVector += amount;
}
void Transformable::scale(glm::vec3 amount) {
    this->scaleVector += amount;
}
void Transformable::rotate(glm::vec3 amount) {
    this->thetaVector += amount;
}
//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
glm::mat4 Transformable::getTransformationMatrix() {
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), this->positionVector);
    glm::mat4 scaleMatrix    = glm::scale(glm::mat4(1.0f), this->scaleVector);
    glm::mat4 rotationMatrix =
        glm::rotate(glm::mat4(1.0f), glm::radians(this->thetaVector.x),
                    glm::normalize(this->xRotationAxis)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(this->thetaVector.y),
                    glm::normalize(this->yRotationAxis)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(this->thetaVector.z),
                    glm::normalize(this->zRotationAxis));
    this->transformationMatrix =
        translationMatrix * scaleMatrix * rotationMatrix;
    return this->transformationMatrix;
}
glm::vec3 Transformable::getPosition() {
    return this->positionVector;
}
glm::vec3 Transformable::getScale() {
    return this->scaleVector;
}
glm::vec3 Transformable::getRotation() {
    return this->thetaVector;
}
// namespace models
