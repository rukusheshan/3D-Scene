#include "windowManager.h"

windowManager::windowManager()
{
	mouseFirstMoved = true;
	lastX = WIDTH / 2;
	lastY = HEIGHT / 2;
	prevTime = 0.0f;
	xChange = 0.0f;
	yChange = 0.0f;
	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
}


windowManager::~windowManager()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void windowManager::init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "SUPER CRATES", NULL, NULL);
	glfwMakeContextCurrent(window);

	CreateCallBacks();

	glewExperimental = true;
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowUserPointer(window, this);
}

void windowManager::preRender()
{
	glClearColor(0.9f, 0.5f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void windowManager::update()
{
	postRender();
}

void windowManager::postRender()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool windowManager::closeNotRequested()
{
	return glfwWindowShouldClose(window) == 0;
}

void windowManager::calculateDelta()
{
	currTime = glfwGetTime();
	delta = prevTime - currTime;
	prevTime = currTime;
}

float windowManager::getDelta()
{
	return delta;
}

GLfloat windowManager::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat windowManager::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void windowManager::CreateCallBacks()
{
	glfwSetKeyCallback(window, HandleKeys);
	glfwSetCursorPosCallback(window, HandleMouse);
	glfwSetWindowSizeCallback(window, HandleWindow);
	glfwSetScrollCallback(window, HandleScroll);
}

void windowManager::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	windowManager* theWindow = static_cast<windowManager*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key > 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
		}
	}
}

void windowManager::HandleMouse(GLFWwindow* window, double xPos, double yPos)
{
	windowManager* theWindow = static_cast<windowManager*>(glfwGetWindowUserPointer(window));
	if (theWindow->mouseFirstMoved) {
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}
	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

}

 void windowManager::HandleWindow(GLFWwindow* window, int width, int height)
{
	 glViewport(0, 0, width, height);
}

 void windowManager::HandleScroll(GLFWwindow* window, double xOffset, double yOffSet)
 {
	 Camera camera;
	 camera.ProcessScroll(yOffSet);
 }
