#include "Camera.h"

Camera::Camera() {
}

Camera::Camera(float fov, float aspect, float nearPlane, float farPlane, 
	glm::vec3 startPos, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	this->fov = fov;
	this->aspect = aspect;
	this->nearPlane = nearPlane;
    this->farPlane = farPlane;
	position = startPos;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	projection = glm::perspective(fov, aspect, nearPlane, farPlane); 
	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;
	Update();
}

void Camera::Update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
	combined = projection * CalculateViewMatrix();
}

void Camera::KeyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;
	if (keys[GLFW_KEY_W])
	{
		position -= front * velocity;
	}
	if (keys[GLFW_KEY_S])
	{
		position += front * velocity;
	}
	if (keys[GLFW_KEY_A])
	{
		position += right * velocity;
	}
	if (keys[GLFW_KEY_D])
	{
		position -= right * velocity;
	}
}

void Camera::MouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw -= xChange;
	pitch -= yChange;
	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}
	Update();
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

Camera::~Camera()
{
}
