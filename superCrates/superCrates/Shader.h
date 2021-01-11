#pragma once
#include<GL/glew.h>
#include<iostream>
#include<fstream>
#include<string>

class Shader
{
	int m_ShaderID = -1;
	GLuint vertexShaderID;
	GLuint fragmemtShaderID;
public:
	Shader(const char* vertexFile, const char* fragmentFile);
	~Shader();

	unsigned int shaderProgram;
	int loadShader(const char* fileName, int type); 
	int transformLoc, combinedLoc, viewPosLoc,
		ambLoc, diffLoc, specLoc,
		lightPosLoc, ambLightLoc, diffLightLoc, specLightLoc,
		constLoc, lineLoc, quadLoc;
	void start();
	int shaderLinker();
	void bindAttributes();
};

