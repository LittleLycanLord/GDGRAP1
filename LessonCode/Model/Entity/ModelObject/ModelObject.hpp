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
			GLuint shaderProg;
			glm::mat4 projection_matrix;
			glm::mat4 view_matrix;
			GLuint texture;
		public:
			ModelObject(GLuint* shaderProg, glm::mat4* view_matrix, GLuint* texture);
		public:
			void updateModel(glm::mat4* view_matrix);
			void drawModel(std::vector<GLuint>* mesh_indices);
		public:
			Matrix* getMatrix();
	};
}