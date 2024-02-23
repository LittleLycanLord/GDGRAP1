#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace matrix {
	class Matrix {
	private:
		float fTranslate_X;
		float fTranslate_Y;
		float fTranslate_Z;

		float fScale_X;
		float fScale_Y;
		float fScale_Z;

		float fTheta;
		float fAxis_X;
		float fAxis_Y;
		float fAxis_Z;

		float fPerspectiveTheta;
		glm::mat4 transformation_matrix;

	public:
		Matrix();
	public:
		void initializeTransformMatrix();
	public:
		void calculateTransformMatrix();
		
	public:
		void setTranslateVar(char cVar, float fValue);
		float getTranslateVar(char cVar);
		void setScaleVar(char cVar, float fValue);
		float getScaleVar(char cVar);
		void setRotateVar(char cVar, float fValue);
		float getRotateVar(char cVar);
		float getPerspectiveTheta();
		void setTransformMatrix(glm::mat4 value);
		glm::mat4* getTransformMatrix();
	};
}