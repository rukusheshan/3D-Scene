#pragma once
#include "Mesh.h"
#include<vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Model 
{
public:
	Model();
	~Model();

	void setPosition(float x, float y, float z);
	void RotateObject(float angle);
	void update(float delta);

	glm::mat4& getTransform() {
		return transform;
	}

	void addMesh(Mesh* m) { meshes.push_back(m); }
	
	const std::vector<Mesh*>& getMeshes() { return meshes; }

private:
	std::vector<Mesh*> meshes;
	glm::mat4 transform;
	glm::vec3 position;
	float rotAngle = 90.0f;
};

