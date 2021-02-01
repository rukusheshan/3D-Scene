#include "Mesh.h"

Mesh::Mesh(unsigned int vaoID, unsigned int numIndices,unsigned int EBO, unsigned int textureID):
	vaoID(vaoID), numIndices(numIndices), eboID(EBO), textureID(textureID)
{
}

Mesh::~Mesh()
{
}

