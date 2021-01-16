#pragma once
#include "Mesh.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Model : public Mesh
{
public:
	Model(unsigned int vaoID);
	~Model();

	void setPosition(float x, float y, float z);
	void RotateObject(float angle);
	void update(float delta);

	glm::mat4& getTransform() {
		return transform;
	}
	
	glm::mat4 transform;
	glm::vec3 position;
	float rotAngle = 90.0f;
};

