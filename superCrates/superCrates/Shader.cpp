#include "Shader.h"

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	vertexShaderID = loader.loadShader(vertexFile, GL_VERTEX_SHADER);
	fragmemtShaderID = loader.loadShader(fragmentFile, GL_FRAGMENT_SHADER);

	m_ShaderID = shaderLinker();
	
}

void Shader::start()
{
	glUseProgram(shaderProgram);
}
int Shader::shaderLinker()
{
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderID);
	glAttachShader(shaderProgram, fragmemtShaderID);
	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);
	bindAttributes();
	return shaderProgram;
}

Shader::~Shader()
{
}

void Shader::bindAttributes()
{
	transformLoc = glGetUniformLocation(shaderProgram, "transform");
	combinedLoc = glGetUniformLocation(shaderProgram, "combined");
	ambLoc = glGetUniformLocation(shaderProgram, "material.ambient");
	diffLoc = glGetUniformLocation(shaderProgram, "material.diffuse");
	specLoc = glGetUniformLocation(shaderProgram, "material.specular");
	ambLightLoc = glGetUniformLocation(shaderProgram, "light.ambient");
	diffLightLoc = glGetUniformLocation(shaderProgram, "light.diffuse");
	specLightLoc = glGetUniformLocation(shaderProgram, "light.specular");
	constLoc = glGetUniformLocation(shaderProgram, "light.constant");
	lineLoc = glGetUniformLocation(shaderProgram, "light.linear");
	quadLoc = glGetUniformLocation(shaderProgram, "light.quadratic");
	viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
	lightPosLoc = glGetUniformLocation(shaderProgram, "light.position");
}
