#pragma once
#include <GL/glew.h>
#include <SOIL.h>
#include <iostream>
#include<vector>
#include<GL/glew.h>
#include <glm.hpp>
using namespace std;

class Loader
{
public:
	Loader();
	~Loader();

	int loadPlane(float* vertices, int numVertices, int* indices, int numIndices);
	int loadCube(float* cube, int numVertices);
	int loadModel(vector<float> vertices, vector<float> normals, vector<float> texCoords, vector<int> indices);

	int loadTexture(const char* fileName);
};

