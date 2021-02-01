#pragma once
#include <GL\glew.h>

class Mesh
{
public:
	Mesh(unsigned int vaoID, unsigned int numIndices, unsigned int EBO, unsigned int textureID);
	~Mesh();

	unsigned int getnumIndices() {
		return numIndices;
	}
	unsigned int getTextureID()
	{
		return textureID;
	}
	unsigned int getVAO() {
		return vaoID;
	}
	unsigned int getEBO() { return eboID; }

private:
	unsigned int vaoID, numIndices, eboID, textureID;
};

