#include "Texture.h"



Texture::Texture(int textureID)
{
	this->textureID = textureID;
}


Texture::~Texture()
{
}

int Texture::loadTexture()
{
	return textureID;
}
