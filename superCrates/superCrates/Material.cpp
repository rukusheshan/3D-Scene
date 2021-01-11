#include "Material.h"



Material::Material()
{
	setAmbient(1.0f, 0.5f, 0.31f);
	setDiffuse(1.0f, 0.5f, 0.31f);
	setSpecular(1.0f, 0.5f, 0.31f);
}


Material::~Material()
{
}

void Material::setAmbient(float x, float y, float z)
{
	ambient.x = x;
	ambient.y = y;
	ambient.z = z;
}

void Material::setDiffuse(float x, float y, float z)
{
	diffuse.x = x;
	diffuse.y = y;
	diffuse.z = z;
}

void Material::setSpecular(float x, float y, float z)
{
	specular.x = x;
	specular.y = y;
	specular.z = z;
}
