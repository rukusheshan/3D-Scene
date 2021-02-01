#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include"Camera.h"
class windowManager
{
public:
	windowManager();
	~windowManager();

	void init();
	void preRender();
	void update();
	void postRender();
	bool closeNotRequested();
	int HEIGHT, WIDTH;
	void calculateDelta();
	float getDelta();
	GLfloat getXChange();
	GLfloat getYChange();
	bool* getKeys() { return keys; }

private:
	GLFWwindow* window;
	float prevTime, currTime, delta;
	bool keys[1024];

	GLfloat lastX, lastY, xChange, yChange;
	bool mouseFirstMoved;

	void CreateCallBacks();
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
	static void HandleWindow(GLFWwindow* window, int width, int height);
	static void HandleScroll(GLFWwindow* window, double xOffset, double yOffSet);
};

