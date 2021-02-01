#include "Model.h"


Model::Model()
{
	setPosition(0.0f, 0.0f, 0.0f);
}


Model::~Model()
{
}

void Model::setPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Model::RotateObject(float angle)
{
	rotAngle = angle;
}


void Model::update(float delta)
{
	transform = glm::mat4(1);
	transform = glm::rotate(transform, rotAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::translate(transform, position);
//	transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
}

