#include "BaseObject.hpp"

using namespace models;

BaseObject::BaseObject() {}

void BaseObject::initialize() {
    this->objFilePath = "Model/Ayaya.obj";
    bool success = tinyobj::LoadObj(&this->attributes, &this->shapes, &this->material, &this->warning, &this->error, this->objFilePath.c_str());
    if (!success) {
        std::cout << "ERROR LOADING OBJECT!" << std::endl;
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