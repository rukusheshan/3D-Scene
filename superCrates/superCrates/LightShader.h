#pragma once
#include <GL\glew.h>
#include <iostream>

class LightShader
{
public:
	LightShader();
	~LightShader();
	unsigned int lightShaderProg;

	void bindAttributes();
	int transformLoc, combinedLoc;
};

