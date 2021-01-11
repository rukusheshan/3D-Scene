#include "Model.h"


Model::Model(unsigned int vaoID):
	Mesh(vaoID, 0)
{
	//setPosition(0.3f, 0.1f, 0.0f);
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

void Model::update(float delta)
{
	transform = glm::mat4(1);
	transform = glm::translate(transform, position);
	//transform = glm::rotate(transform, rotAngle += 2.0f * delta, glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(0.25f, 0.25f, 0.25f));
}
