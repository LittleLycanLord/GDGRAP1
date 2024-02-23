#include "Matrix.hpp"

using namespace matrix;

Matrix::Matrix() {
	this->initializeTransformMatrix();
}

void Matrix::initializeTransformMatrix() {
	this->fTranslate_X = 0.0f;
	this->fTranslate_Y = 0.0f;
	this->fTranslate_Z = -2.0f;

	this->fScale_X = 0.95f;
	this->fScale_Y = 0.95f;
	this->fScale_Z = 0.95f;

	this->fTheta = 90.0f;
	this->fAxis_X = 0.0f;
	this->fAxis_Y = 1.0f;
	this->fAxis_Z = 0.0f;

	this->fPerspectiveTheta = 60.0f;
	this->transformation_matrix = glm::mat4(1.0f);
}

void Matrix::calculateTransformMatrix() {

	glm::mat4 identity_matrix = glm::mat4(1.0f);

	this->transformation_matrix = glm::translate(identity_matrix, glm::vec3(this->fTranslate_X, this->fTranslate_Y, this->fTranslate_Z));

	this->transformation_matrix = glm::scale(this->transformation_matrix, glm::vec3(this->fScale_X, this->fScale_Y, this->fScale_Z));

	this->transformation_matrix = glm::rotate(this->transformation_matrix, glm::radians(this->fTheta), glm::normalize(glm::vec3(this->fAxis_X, this->fAxis_Y, this->fAxis_Z)));
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
		this->fAxis_X = fValue;
		break;
	case 'Y':
		this->fAxis_Y = fValue;
		break;
	case 'Z':
		this->fAxis_Z = fValue;
		break;
	case 'T':
		this->fTheta = fValue;
		break;
	}
}

float Matrix::getRotateVar(char cVar) {
	switch (cVar) {
	case 'X':
		return this->fAxis_X;
	case 'Y':
		return this->fAxis_Y;
	case 'Z':
		return this->fAxis_Z;
	case 'T':
		return this->fTheta;
	}

	return 0.0f;
}

float Matrix::getPerspectiveTheta() {
	return this->fPerspectiveTheta;
}

void Matrix::setTransformMatrix(glm::mat4 value) {
	this->transformation_matrix = value;
}

glm::mat4* Matrix::getTransformMatrix() {
	return &this->transformation_matrix;
}
