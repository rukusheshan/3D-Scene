#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
class Light
{
public:
	Light();
	~Light();

	glm::vec3 position;
	glm::mat4 transform;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float constant, linear, quadratic;

	glm::mat4& getTransform() {
		return transform;
	}

	glm::vec3& getambient() {
		return ambient;
	}

	glm::vec3& getdiffuse() {
		return diffuse;
	}

	glm::vec3& getspecular() {
		return specular;
	}

	void setPosition(float x, float y, float z);
	void setAmbient(float x, float y, float z);
	void setDiffuse(float x, float y, float z);
	void setSpecular(float x, float y, float z);
};

