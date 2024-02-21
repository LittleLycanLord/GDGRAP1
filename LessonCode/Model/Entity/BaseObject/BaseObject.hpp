#pragma once

#include "../../tiny_obj_loader.h"
#include "iostream"
namespace models {
	class BaseObject {
		private:
			std::string objFilePath;
			std::vector<tinyobj::shape_t> shapes;
			std::vector<tinyobj::material_t> material;
			std::string warning;
			std::string error;
			tinyobj::attrib_t attributes;
		public:
			BaseObject();
		public:
			std::string getObjFilePath();
			std::vector<tinyobj::shape_t>* getShapes();
			std::vector<tinyobj::material_t>* getMaterial();
			std::string* getWarningString();
			std::string* getErrorString();
			tinyobj::attrib_t* getObjAttributes();
	};
}	