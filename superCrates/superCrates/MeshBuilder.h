#pragma once

class MeshBuilder
{
public:
	MeshBuilder();
	~MeshBuilder();

	float plane[32] = {
		25.0f,  0.0f, 25.0f,  1.0f, 1.0f,		0.0f, 1.0f, 0.0f, 	//top right
		25.0f, 0.0f, -25.0f,  1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	//bottom right
		-25.0f, 0.0f, -25.0f,  0.0f, 0.0f,	0.0f, 1.0f, 0.0f,	//bottom left
		-25.0f,  0.0f, 25.0f,  0.0f, 1.0f,	0.0f, 1.0f, 0.0f	//top left
	};

	float vertices[20] = {
		0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 0.1f
	};

	int indices[6] = {
		0, 1, 3,
		1, 2, 3
	};

	float size = 0.5f;
	float cube[288] = {
	-size, -size, -size, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
	 size, -size, -size, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
	 size,  size, -size, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
	 size,  size, -size, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
	-size,  size, -size, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
	-size, -size, -size, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

	-size, -size,  size, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	 size, -size,  size, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	 size,  size,  size, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	 size,  size,  size, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-size,  size,  size, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-size, -size,  size, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

	-size,  size,  size, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	-size,  size, -size, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
	-size, -size, -size, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
	-size, -size, -size, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
	-size, -size,  size, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	-size,  size,  size, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

	 size,  size,  size, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	 size,  size, -size, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 size, -size, -size, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 size, -size, -size, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 size, -size,  size, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	 size,  size,  size, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	 
	-size, -size, -size, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
	 size, -size, -size, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
	 size, -size,  size, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
	 size, -size,  size, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
	-size, -size,  size, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
	-size, -size, -size, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

	-size,  size, -size, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	 size,  size, -size, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	 size,  size,  size, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	 size,  size,  size, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	-size,  size,  size, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	-size,  size, -size, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f
	};
};

