#include "Shader.h"

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
	fragmemtShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);

	m_ShaderID = shaderLinker();
	
}

int Shader::loadShader(const char* fileName, int type)
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
