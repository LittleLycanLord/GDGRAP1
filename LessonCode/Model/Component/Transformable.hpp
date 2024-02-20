#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace std;

namespace components {
class Transformable {
    //* ╔════════════╗
    //* ║ Attributes ║
    //* ╚════════════╝
private:
    glm::mat4 transformationMatrix;
    //* Position Vector
    glm::vec3 positionVector;
    //* Scale Vector
    glm::vec3 scaleVector;
    //* Rotation Axes
    const glm::vec3 xRotationAxis = glm::vec3(1.0f, 0.0f, 0.0f );
    const glm::vec3 yRotationAxis = glm::vec3(0.0f, 1.0f, 0.0f );
    const glm::vec3 zRotationAxis = glm::vec3(0.0f, 0.0f, 1.0f );
    //* Rotation Thetas
    glm::vec3 thetaVector;

    //* ╔═══════════════════════════════╗
    //* ║ Constructors & Deconstructors ║
    //* ╚═══════════════════════════════╝
public:
    Transformable();
    Transformable(glm::vec3 position);
    virtual ~Transformable() = 0;
    //* ╔═════════╗
    //* ║ Methods ║
    //* ╚═════════╝
public:
    void translate(glm::vec3 amount);
    void scale(glm::vec3 amount);
    void rotate(glm::vec3 amount);
    //* ╔═══════════════════╗
    //* ║ Getters & Setters ║
    //* ╚═══════════════════╝
public:
    glm::mat4 getTransformationMatrix();
    glm::vec3 getPosition();
    glm::vec3 getScale();
    glm::vec3 getRotation();
};
}  // namespace components