#pragma once
#include <GL/glew.h>
#include <SOIL.h>
#include <iostream>

class Texture
{
public:
	Texture(int textureID);
	~Texture();

	int textureID;
	int loadTexture();
};

