#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Plane
{
public:
	Plane();
	~Plane();

	void setPosition(float x, float y, float z);
	void update();

	glm::mat4& getTransform() {
		return transform;
	}

	glm::mat4 transform;
	glm::vec3 position;

};

