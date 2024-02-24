#include "Camera.hpp"

using namespace models;

Camera::Camera() { this->initializeCamera(); }

void Camera::initializeCamera() {
    //* Translation Vector
    this->translate              = glm::vec3(0.0f, 0.0f, 0.0f);
    //* Scale Vector
    this->scale                  = glm::vec3(1.0f, 1.0f, 1.0f);
    //* Rotation Axes
    this->xRotationAxis          = glm::vec3(1.0f, 0.0f, 0.0f);
    this->yRotationAxis          = glm::vec3(0.0f, 1.0f, 0.0f);
    this->zRotationAxis          = glm::vec3(0.0f, 0.0f, 1.0f);
    //* Rotation Thetas
    this->theta                  = glm::vec3(0.0f, 0.0f, 0.0f);
    //* Camera Position
    this->cameraPosition         = glm::vec3(0.0, 0, 10.f);
    this->pseudoMousePosition    = glm::vec2(0.0f, 0.0f);
    this->pseudoOldMousePosition = glm::vec2(0.0f, 0.0f);
    this->centerPosition         = glm::vec3(0.0, 0.f, -1.f);
}

void Camera::updateCamera(int key, int action, float* FOV, glm::vec3 WorldUp) {
    //* Rates of Change
    float movementSpeed       = 0.3f;
    float scalingRate         = 0.05f;
    float zoomRate            = 10.f;
    glm::vec3 strafeDirection = glm::cross(centerPosition, WorldUp);
    switch (key) {
        //* Moving:
        case GLFW_KEY_W:
            cameraPosition += movementSpeed * centerPosition;
            break;
        case GLFW_KEY_A:
            cameraPosition -= movementSpeed * strafeDirection;
            break;
        case GLFW_KEY_S:
            cameraPosition -= movementSpeed * centerPosition;
            break;
        case GLFW_KEY_D:
            cameraPosition += movementSpeed * strafeDirection;
            break;
        case GLFW_KEY_LEFT_SHIFT:
            cameraPosition += movementSpeed * WorldUp;
            break;
        case GLFW_KEY_LEFT_CONTROL:
            cameraPosition -= movementSpeed * WorldUp;
            break;
            //* Rotating:
        case GLFW_KEY_UP:
            this->pseudoMousePosition.y += this->rotateSpeed;
            this->theta.x -= this->rotateSpeed * 57.2958f; //? PI -> Degrees
            break;
        case GLFW_KEY_DOWN:
            this->pseudoMousePosition.y -= this->rotateSpeed;
            this->theta.x += this->rotateSpeed * 57.2958f; //? PI -> Degrees
            break;
        case GLFW_KEY_LEFT:
            this->pseudoMousePosition.x -= this->rotateSpeed;
            this->theta.y -= this->rotateSpeed * 57.2958f; //? PI -> Degrees
            break;
        case GLFW_KEY_RIGHT:
            this->pseudoMousePosition.x += this->rotateSpeed;
            this->theta.y += this->rotateSpeed * 57.2958f; //? PI -> Degrees
            break;
            //* Zooming:
        case GLFW_KEY_Z:
            *FOV -= zoomRate;
            break;
        case GLFW_KEY_X:
            *FOV += zoomRate;
            break;
    }
    glm::vec2 mouseDelta =
        this->pseudoMousePosition - this->pseudoOldMousePosition;

    glm::vec3 vecData = this->cameraPosition + this->centerPosition;

    this->centerPosition =
        glm::mat3(glm::rotate(-mouseDelta.x, WorldUp)) * this->centerPosition;
    this->centerPosition =
        glm::mat3(glm::rotate(mouseDelta.y,
                              glm::cross(this->centerPosition, WorldUp))) *
        this->centerPosition;
    this->pseudoOldMousePosition = this->pseudoMousePosition;
    this->viewMatrix =
        glm::lookAt(this->cameraPosition,
                    this->cameraPosition + this->centerPosition, WorldUp);
}

glm::mat4* Camera::getViewMatrix() { return &this->viewMatrix; }
glm::vec3* Camera::getCameraPosition() { return &this->cameraPosition; }
glm::vec3* Camera::getCenterPosition() { return &this->centerPosition; }
glm::vec3* Camera::getTheta() { return &this->theta; }