#pragma once


#include <GL/glew.h>
#include <glm.hpp>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>


class Camera
{
public:
	Camera();
	Camera(float fov, float aspect, float nearPlane, float farPlane, glm::vec3 startPos, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
	~Camera();
	glm::mat4& getCombined() {
		return combined;
	}
	void ProcessScroll(float yOffSet);
	void KeyControl(bool* keys, GLfloat deltaTime);
	void MouseControl(GLfloat xChange, GLfloat yChange);
	glm::vec3 getCameraPosition();
	glm::mat4 CalculateViewMatrix();
	float fov, aspect, nearPlane, farPlane;
	glm::vec3 position;
private:
	GLfloat moveSpeed, turnSpeed, pitch, yaw;
	glm::vec3 up, front, right,  worldUp;
	glm::mat4 combined;
	glm::mat4 projection;

	void Update();
};

