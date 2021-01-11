#pragma once
#include <glm.hpp>
class Material
{
public:
	Material();
	~Material();

	glm::vec3 viewPos;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	glm::vec3& getambient() {
		return ambient;
	}

	glm::vec3& getdiffuse() {
		return diffuse;
	}

	glm::vec3& getspecular() {
		return specular;
	}

	void setAmbient(float x, float y, float z);
	void setDiffuse(float x, float y, float z);
	void setSpecular(float x, float y, float z);

};

