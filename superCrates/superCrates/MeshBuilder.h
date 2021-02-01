#pragma once
#include <iostream>
#include <glm.hpp>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct TextureData {
	unsigned int id;
	std::string type;
	std::string path;
};

struct LoaderData {
	unsigned int vao, ebo, indexCount, textureID;
};

class MeshBuilder
{
public:
	MeshBuilder();
	~MeshBuilder();

	float plane[32] = {
		25.0f,  0.0f, 25.0f,  1.0f, 1.0f,		0.0f, 1.0f, 0.0f, 	//top right
		25.0f, 0.0f, -25.0f,  1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	//bottom right
		-25.0f, 0.0f, -25.0f,  0.0f, 0.0f,	    0.0f, 1.0f, 0.0f,	//bottom left
		-25.0f,  0.0f, 25.0f,  0.0f, 1.0f,		0.0f, 1.0f, 0.0f	//top left
	};

	float vertices[20] = {
		0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 0.1f
	};

	unsigned int indices[6] = {
		0, 1, 3,
		1, 2, 3
	};

	float size = 0.5f;

float cubeVertices[192] = {
	-size, -size, -size, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, //0
	 size, -size, -size, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, //1
	 size,  size, -size, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, //2
	-size,  size, -size, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, //3

	-size, -size,  size, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, //4
	 size, -size,  size, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, //5
	 size,  size,  size, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, //6 
	-size,  size,  size, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //7

	-size,  size,  size, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, //8 
	-size,  size, -size, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, //9
	-size, -size, -size, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, //10
	-size, -size,  size, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, //11

	 size,  size,  size, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, //12
	 size,  size, -size, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //13
	 size, -size, -size, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, //14
	 size, -size,  size, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //15

	-size, -size, -size, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, //16
	 size, -size, -size, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, //17
	 size, -size,  size, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, //18
	-size, -size,  size, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, //19

	-size,  size, -size, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //20
	 size,  size, -size, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //21
	 size,  size,  size, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //22
	-size,  size,  size, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f  //23
};

unsigned int cubeIndices[36] = { 
	0, 1, 3,
	1, 2, 3,
	4, 5, 7, 
	5, 6, 7,
	8, 9, 11,
	9, 10, 11,
	12, 14, 15,
	13, 14, 15,
	16, 18, 19,
	17, 18, 19,
	20, 22, 23,
	21, 22, 23
};

};

