#include "Light.h"



Light::Light()
{
	setPosition(-0.5f, 0.5f, 0.0f);
	setAmbient(0.5f, 0.5f, 0.5f);
	setDiffuse(0.7f, 0.7f, 0.7f);
	setSpecular(1.0f, 1.0f, 1.0f);
	constant = 1.0f;
	linear = 0.09f; 
	quadratic = 0.032f;
}


Light::~Light()
{
}

void Light::setPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	transform = glm::translate(glm::mat4(1), position);
	transform = glm::scale(transform, glm::vec3(0.05f));
}

void Light::setAmbient(float x, float y, float z)
{
	ambient.x = x;
	ambient.y = y;
	ambient.z = z;
}

void Light::setDiffuse(float x, float y, float z)
{
	diffuse.x = x;
	diffuse.y = y;
	diffuse.z = z;
}

void Light::setSpecular(float x, float y, float z)
{
	specular.x = x;
	specular.y = y;
	specular.z = z;
}

