#include "BaseObject.hpp"

using namespace models;

BaseObject::BaseObject() {}

void BaseObject::initialize() {
    this->objFilePath = "Model/Knuckles.obj";
    bool success = tinyobj::LoadObj(&this->attributes, &this->shapes, &this->material, &this->warning, &this->error, this->objFilePath.c_str());
    if (!success) {
        std::cout << "ERROR LOADING OBJECT!" << std::endl;
        return;
    }
    for (tinyobj::index_t vData : this->shapes[0].mesh.indices) {
        //*Insert Vertex Position Data: (X, Y, Z)
        this->fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3)]);
        this->fullVertexData.push_back(
            attributes.vertices[(vData.vertex_index * 3) + 1]);
        this->fullVertexData.push_back(
            attributes.vertices[(vData.vertex_index * 3) + 2]);
        //*Insert Normals Position Data: (X, Y, Z)
        this->fullVertexData.push_back(attributes.normals[(vData.normal_index * 3)]);
        this->fullVertexData.push_back(
            attributes.normals[(vData.normal_index * 3) + 1]);
        this->fullVertexData.push_back(
            attributes.normals[(vData.normal_index * 3) + 2]);
        //* Insert UV Data: (U, V)
        this->fullVertexData.push_back(
            attributes.texcoords[(vData.texcoord_index * 2)]);
        this->fullVertexData.push_back(
            attributes.texcoords[(vData.texcoord_index * 2) + 1]);
    }
}

std::string BaseObject::getObjFilePath() {
    return this->objFilePath;
}

std::vector<tinyobj::shape_t>* BaseObject::getShapes() {
    return &this->shapes;
}

std::vector<tinyobj::material_t>* BaseObject::getMaterial() {
    return &this->material;
}

std::string* BaseObject::getWarningString() {
    return &this->warning;
}

std::string* BaseObject::getErrorString() {
    return &this->error;
}

tinyobj::attrib_t* BaseObject::getObjAttributes() {
    return &this->attributes;
}

std::vector<GLfloat>* BaseObject::getFullVertexData() {
    return &this->fullVertexData;
}