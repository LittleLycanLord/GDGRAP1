#include "Camera.hpp"

using namespace models;

Camera::Camera() {
    this->initializeCamera();
}


void Camera::initializeCamera() {

    //* Translation Vector
    this->translate = glm::vec3(0.0f, 0.0f, 0.0f);
    //* Scale Vector
    this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
    //* Rotation Axes
    this->xRotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
    this->yRotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    this->zRotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
    //* Rotation Thetas
    this->theta = glm::vec3(0.0f, 0.0f, 0.0f);
    //* Camera Position
    this->cameraPosition = glm::vec3(0.0, 0, 10.f);
    this->centerPosition = glm::vec3(0.0, 3.f, 0.f);

    this->WorldUp = glm::vec3(0, 1.0f, 0);

    this->viewMatrix = glm::lookAt(this->cameraPosition, this->centerPosition, this->WorldUp);
}
void Camera::updateCamera(int key, float* FOV) {
    //* Rates of Change
    float movementSpeed = 0.1f;
    float rotateSpeed = 10.f;
    float scalingRate = 0.05f;
    float zoomRate = 10.f;

    switch (key) {
        //* Moving:
        case GLFW_KEY_W: 
           // if (action == GLFW_PRESS) {
            // translate.y += movementSpeed;
            cameraPosition.z -= movementSpeed;
            centerPosition.z -= movementSpeed;
            // }
            break;
        case GLFW_KEY_A:
            // translate.x -= movementSpeed;
            cameraPosition.x -= movementSpeed;
            centerPosition.x -= movementSpeed;
            break;
        case GLFW_KEY_S:
            // translate.y -= movementSpeed;
            cameraPosition.z += movementSpeed;
            centerPosition.z += movementSpeed;
            break;
        case GLFW_KEY_D:
            // translate.x += movementSpeed;
            cameraPosition.x += movementSpeed;
            centerPosition.x += movementSpeed;
            break;
            //* Rotating:
        case GLFW_KEY_UP:
            theta.x -= rotateSpeed;
            break;
        case GLFW_KEY_DOWN:
            theta.x += rotateSpeed;
            break;
        case GLFW_KEY_LEFT:
            theta.y -= rotateSpeed;
            break;
        case GLFW_KEY_RIGHT:
            theta.y += rotateSpeed;
            break;
            //* Zooming:
        case GLFW_KEY_Z:
            *FOV -= zoomRate;
            break;
        case GLFW_KEY_X:
            *FOV += zoomRate;
            break;
        }

    this->viewMatrix = glm::lookAt(this->cameraPosition, this->centerPosition, this->WorldUp);
}

glm::mat4* Camera::getViewMatrix() { 
    return &this->viewMatrix; 
}