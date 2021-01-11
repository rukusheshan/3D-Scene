#include "Plane.h"



Plane::Plane()
{
	setPosition(0.0, 0.0, 0.0);
}


Plane::~Plane()
{
}

void Plane::setPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Plane::update()
{
	transform = glm::mat4(1);
	transform = glm::translate(transform, position);
	transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
}