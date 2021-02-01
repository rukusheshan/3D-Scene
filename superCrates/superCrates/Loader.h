#pragma once
#include <GL/glew.h>
#include <SOIL.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include<iostream>
#include<fstream>
#include<string>
#include <vector>

#include "MeshBuilder.h"
using namespace std;

class Loader
{
public:
	Loader();
	~Loader();

	LoaderData CreateMesh(float* vertices, int numVertices, unsigned int* indices, int numIndices);
	int LoadTexture(const char* fileName);
	int loadShader(const char* fileName, int type);
	int loadOBJModel(vector<float> vertices, vector<float> normals, vector<float> texCoords, vector<int> indices);

	vector<LoaderData> LoadModel(const std::string& fileName);

private:
	
	LoaderData LoadMesh(aiMesh* mesh, const aiScene* scene);
	vector<LoaderData> LoadNode(aiNode* node, const aiScene* scene);
	void LoadMaterials(const aiScene* scene);
};

