#pragma once
#include <iostream>
#include <stdio.h>
#include <glm.hpp>
#include <vector>
using namespace std;

class OBJLoader
{
private:
	std::vector<glm::vec3> newVector;
	std::vector<float> vertices;
	std::vector<float> texture;
	std::vector<float> normals;
	std::vector<int> faceVertices;

public:
	OBJLoader();
	~OBJLoader();
	void LoadFromFile(const char* fileName);

//	std::vector<glm::vec3> getNewVector() { return newVector; };
	std::vector<int> getFaceVertices() { return faceVertices; };
	std::vector<float> getVertices() { return vertices; };
	std::vector<float> getTexCoords() { return texture; };
	std::vector<float> getNormals() { return normals; };
};

