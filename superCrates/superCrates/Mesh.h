#pragma once
class Mesh
{
public:
	Mesh(unsigned int vaoID, unsigned int numIndices);
	~Mesh();

	unsigned int getvaoID() {
		return vaoID;
	}

	unsigned int getnumIndices() {
		return numIndices;
	}

private:
	unsigned int vaoID, numIndices;
};

