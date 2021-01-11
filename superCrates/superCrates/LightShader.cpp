#include "LightShader.h"

const char *lightVertexShader = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 combined;\n"
"uniform mat4 transform;\n"
"void main()"
"{"
"gl_Position = combined * transform * vec4(aPos, 1.0);\n"
"}\0";

const char *lightFragmentShader = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()"
"{"
"FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
"}\n\0";


LightShader::LightShader()
{
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &lightVertexShader, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &lightFragmentShader, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	lightShaderProg = glCreateProgram();
	glAttachShader(lightShaderProg, vertexShader);
	glAttachShader(lightShaderProg, fragmentShader);
	glLinkProgram(lightShaderProg);

	glGetProgramiv(lightShaderProg, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(lightShaderProg, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	bindAttributes();


}


LightShader::~LightShader()
{
}

void LightShader::bindAttributes()
{
	transformLoc = glGetUniformLocation(lightShaderProg, "transform");
	combinedLoc = glGetUniformLocation(lightShaderProg, "combined");
}