#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "iostream"
#include "string"
#include "vector"

using namespace std;

namespace models {
class Camera {
private:
    glm::vec3 translate;
    glm::vec3 scale;
    glm::vec3 xRotationAxis;
    glm::vec3 yRotationAxis;
    glm::vec3 zRotationAxis;
    glm::vec3 theta;

    float pi            = 3.14159265358979323846f;
    int sectionsPerTick = 64; //TODO: Higher means slower
    float rotateSpeed   = pi / (sectionsPerTick / 2);

private:
    glm::vec3 cameraPosition;
    glm::vec3 centerPosition;
    glm::vec2 pseudoMousePosition;
    glm::vec2 pseudoOldMousePosition;
    glm::mat4 viewMatrix;

public:
    Camera();

public:
    void initializeCamera();
    void updateCamera(int key, int action, float* FOV, glm::vec3 WorldUp);

public:
    glm::mat4* getViewMatrix();
    glm::vec3* getCameraPosition();
    glm::vec3* getCenterPosition();
    glm::vec3* getTheta();
};
}  // namespace models
