#pragma once
#include "../../Component/Transformable.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "iostream"
#include "string"
#include "vector"

using namespace std;

namespace models {
using namespace components;
class Camera : public Transformable {
    //* ╔════════════╗
    //* ║ Attributes ║
    //* ╚════════════╝
    string cameraName;
    glm::vec3 WorldUp;
    glm::vec3 Center;
    //* Camera Position
    glm::vec3 cameraPos;
    glm::mat4 cameraPositionMatrix;

    glm::vec3 forwardVector;
    glm::vec3 rightVector;
    glm::vec3 upVector;

    glm::mat4 cameraOrientation = glm::mat4(1.f);

    glm::mat4 viewMatrix;

public:
    //* ╔═══════════════════════════════╗
    //* ║ Constructors & Deconstructors ║
    //* ╚═══════════════════════════════╝
    Camera(string cameraName);

public:
    //* ╔═════════╗
    //* ║ Methods ║
    //* ╚═════════╝
    void initializeCamera();
    void updateCamera();

    //* ╔═══════════════════╗
    //* ║ Getters & Setters ║
    //* ╚═══════════════════╝
public:
    glm::mat4 getViewMatrix();
    void moveCamera(glm::vec3 cameraPos);
};
}  // namespace models