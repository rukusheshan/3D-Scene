#include "Loader.h"

Loader::Loader()
{
}

Loader::~Loader()
{
}

LoaderData Loader::CreateMesh(float* vertices, int numVertices,unsigned int* indices, int numIndices)
{
	
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * numIndices, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	LoaderData data;
	data.vao = VAO;
	data.ebo = EBO;
	data.indexCount = numIndices;
	return data;
}


int Loader::LoadTexture(const char* fileName)
{
	unsigned char* texture;
	GLuint textureID;
	int width, height;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	texture = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGBA);

	if (texture) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	SOIL_free_image_data(texture);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}

int Loader::loadShader(const char* fileName, int type)
{
	std::string ShaderCode;
	std::ifstream ShaderStream(fileName, std::ios::in);
	if (ShaderStream.is_open()) {
		std::string Line = "";
		while (getline(ShaderStream, Line))
			ShaderCode += "\n" + Line;
		ShaderStream.close();
	}
	else {
		printf("Impossible to open %s", fileName);
		getchar();
		return 0;
	}

	printf("Compiling Shader : %s\n", fileName);
	int	ShaderID = glCreateShader(type);
	char const* SourcePointer = ShaderCode.c_str();
	glShaderSource(ShaderID, 1, &SourcePointer, NULL);
	glCompileShader(ShaderID);

	int success;
	char infoLog[512];
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(ShaderID, 512, NULL, infoLog);
		std::cout << "Vertex shader compilation failed" << infoLog << std::endl;
	}

	return ShaderID;
}

int Loader::loadOBJModel(vector<float> vertices, vector<float> normals, vector<float> texCoords, vector<int> indices)
{
	unsigned int VAO, VBO_V, VBO_T, VBO_N, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &VBO_V);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_V);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(),&vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  0, (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &VBO_T);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_T);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,  0, (void*)0);
	glEnableVertexAttribArray(1);


	glGenBuffers(1, &VBO_N);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_N);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size(), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return VAO;
}

vector<LoaderData> Loader::LoadModel(const std::string& fileName)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
	vector<LoaderData> meshes;
	if (!scene)
	{
		printf("Model (%s) failed to load: %s", fileName, importer.GetErrorString());
		return meshes;
	}

	meshes = LoadNode(scene->mRootNode, scene);

	LoadMaterials(scene);
	return meshes;
}


vector<LoaderData> Loader::LoadNode(aiNode* node, const aiScene* scene)
{
	vector<LoaderData> meshes;
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		meshes.push_back(LoadMesh(scene->mMeshes[node->mMeshes[i]], scene));
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		return LoadNode(node->mChildren[i], scene);
	}
	return meshes;
}

LoaderData Loader::LoadMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
		if (mesh->mTextureCoords[0])
		{
			vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
		}
		else {
			vertices.insert(vertices.end(), { 0.0f, 0.0f });
		}
		vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z });
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
    LoaderData newData = CreateMesh(&vertices[0], vertices.size(), &indices[0], indices.size());
	newData.textureID = mesh->mMaterialIndex;
	
	return newData;
}


void Loader::LoadMaterials(const aiScene* scene)
{
	vector<unsigned int> textureIDs;
	for (size_t i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* material = scene->mMaterials[i];
		textureIDs.push_back( LoadTexture("./Assets/Stall/stallTexture.png"));
	}
}

//void Loader::RenderModel()
//{
//	for (size_t i = 0; i < meshes.size(); i++)
//	{
//		unsigned int materialIndex = meshToTex[i];
//
//		if (materialIndex < textureIDs.size() && textureIDs[materialIndex])
//		{
//			glBindTexture(GL_TEXTURE_2D, textureIDs[materialIndex]);
//		}
//		//render here. bind vao and draw call
//		//meshes[i]->RenderMesh();
//	}
//}