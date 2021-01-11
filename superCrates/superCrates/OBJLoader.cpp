#include "OBJLoader.h"
#include <string>
#include <fstream>

OBJLoader::OBJLoader()
{
}

OBJLoader::~OBJLoader()
{
}

void OBJLoader::LoadFromFile(const char* fileName)
{
	FILE* fp;
	fopen_s(&fp, fileName, "r");

	/*std::ifstream fileData(fileName, std::ios::in);
	if (fileData.is_open()) {
		std::string line = "";
		while (getline(fileData, line)) {
			char tag[2];
			tag[0] = line[0];
			tag[1] = line[1];
			if (strcmp(tag, "v ") == 0)
			{
				glm::vec3 tempvec;
				fscanf_s(fp, "%f%f%f", &tempvec.x, &tempvec.y, &tempvec.z);
				vertices.push_back(tempvec);
			}
			else if (strcmp(tag, "vt") == 0)
			{
				glm::vec2 tempvecTexture;
				fscanf_s(fp, "%f%f", &tempvecTexture.x, &tempvecTexture.y);
				texture.push_back(tempvecTexture);
			}
			else if (strcmp(tag, "vn") == 0)
			{
				glm::vec3 tempvecNormal;
				fscanf_s(fp, "%f%f%f", &tempvecNormal.x, &tempvecNormal.y, &tempvecNormal.z);
				normals.push_back(tempvecNormal);
			}
			else if (strcmp(tag, "f ") == 0)
			{
				glm::vec3 tempfaceVertices[3];
				int v[3], vt[3], vn[3];
				fscanf_s(fp, "%d/%d/%d %d/%d/%d %d/%d/%d", &v[0], &vt[0], &vn[0], &v[1], &vt[1], &vn[1], &v[2], &vt[2], &vn[2]);
				tempfaceVertices[0] = vertices[v[0] - 1];
				tempfaceVertices[1] = vertices[v[1] - 1];
				tempfaceVertices[2] = vertices[v[2] - 1];
				newVector.push_back(tempfaceVertices[0]);
				newVector.push_back(tempfaceVertices[1]);
				newVector.push_back(tempfaceVertices[2]);
			}
		}
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", fileName);
		getchar();
	}
	*/
	while (1)
	{
		char tag[1000];
		int filePos = fscanf(fp, "%s", tag);
		if (filePos == EOF)
		{
			break;
		}
		if (strcmp(tag, "v") == 0)
		{
			float tmpX, tmpY, tmpZ;
			fscanf(fp, "%f%f%f", &tmpX, &tmpY, &tmpZ);
			vertices.push_back(tmpX);
			vertices.push_back(tmpY);
			vertices.push_back(tmpZ);
		}
		else if (strcmp(tag, "vt") == 0)
		{
			float tmpX, tmpY;
			fscanf(fp, "%f%f", &tmpX, &tmpY);
			texture.push_back(tmpX);
			texture.push_back(tmpY);
		}
		else if (strcmp(tag, "vn") == 0)
		{
			float tmpX, tmpY, tmpZ;
			fscanf(fp, "%f%f%f", &tmpX, &tmpY, &tmpZ);
			normals.push_back(tmpX);
			normals.push_back(tmpY);
			normals.push_back(tmpZ);
		}
		else if (strcmp(tag, "f") == 0)
		{
			glm::vec3 tempfaceVertices[3];
			int v[3], vt[3], vn[3];
			fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d", &v[0], &vt[0], &vn[0], &v[1], &vt[1], &vn[1], &v[2], &vt[2], &vn[2]);
			faceVertices.push_back(v[0] - 1); 
			faceVertices.push_back(v[1] - 1); 
			faceVertices.push_back(v[2] - 1);
			newVector.push_back(tempfaceVertices[0]);
			newVector.push_back(tempfaceVertices[1]);
			newVector.push_back(tempfaceVertices[2]);
		}
	}
}
