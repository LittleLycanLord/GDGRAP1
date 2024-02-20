#include "Camera.hpp"

using namespace models;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
Camera::Camera(string cameraName) : Transformable(), cameraName(cameraName) {
    this->initializeCamera();
}

//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝
void Camera::initializeCamera() {
    //* Initialize World Up & Camera Center
    this->WorldUp   = glm::vec3(0, 1.0f, 0);
    this->Center    = glm::vec3(0, 3.0f, 0);
    //* Camera Position
    this->cameraPos = glm::vec3(0, 0, 10.f);
    this->cameraPositionMatrix =
        glm::translate(glm::mat4(1.0f), cameraPos * -1.0f);

    this->forwardVector =
        glm::normalize(glm::vec3(Center - cameraPos));  //* Set Forward Vector
    this->rightVector = glm::normalize(
        glm::cross(forwardVector, WorldUp));  //* Set Right Vector
    this->upVector = glm::normalize(
        glm::cross(rightVector, forwardVector));  //* Set Up Vector

    //* Set Camera Orientation
    this->cameraOrientation = glm::mat4(1.f);
    cameraOrientation[0][0] = rightVector.x;
    cameraOrientation[1][0] = rightVector.y;
    cameraOrientation[2][0] = rightVector.z;
    cameraOrientation[0][1] = upVector.x;
    cameraOrientation[1][1] = upVector.y;
    cameraOrientation[2][1] = upVector.z;
    cameraOrientation[0][2] = -forwardVector.x;
    cameraOrientation[1][2] = -forwardVector.y;
    cameraOrientation[2][2] = -forwardVector.z;
    cout << this->cameraName + " has been initialized!" << endl;
}
void Camera::updateCamera() {
    //* Set View Matrix
    this->viewMatrix =
        // cameraOrientation * cameraPositionMatrix;
        glm::lookAt(this->cameraPos, this->Center, this->WorldUp);
}
//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
glm::mat4 Camera::getViewMatrix() { return this->viewMatrix; }
void Camera::moveCamera(glm::vec3 cameraPos) { this->cameraPos = cameraPos; }
// namespace models