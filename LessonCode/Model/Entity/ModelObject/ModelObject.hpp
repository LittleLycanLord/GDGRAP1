#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "../../Component/Matrix.hpp"
#include "iostream"
#include "vector"

namespace models {
	using namespace matrix;
	class ModelObject {
		private:
			Matrix modelMatrix;

		private:
			glm::mat4 projection_matrix;
			glm::mat4 view_matrix;

		private:
			GLuint shaderProg;
			GLuint texture;
		
		private:
			bool isInitialized;

		public:
			ModelObject();
		public:
			void initialize(GLuint* shaderProg, glm::mat4* view_matrix, GLuint* texture);
			void updateModel();
			void setModelInFrontOfCam(glm::vec3* cameraPosition, glm::vec3* centerPosition);
			void drawModel(std::vector<GLuint>* mesh_indices);
		public:
			void setViewMatrix(glm::mat4 viewMatrix);
			Matrix* getMatrix();
	};
}