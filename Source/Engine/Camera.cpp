#include "stdafx.h"
#include "Camera.h"


Camera::Camera(int width, int height)
{
	position = glm::vec3(0.0f, 0.0f, 3.0f);
	target = glm::vec3(0.0f, 0.0f, 0.0f);
	direction = glm::normalize(position - target);
	right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), direction));
	up = glm::cross(direction, right);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	//view = glm::lookAt(position, position + front, up);

	screenWidth = width;
	screenHeight = height;
}

void Camera::Control(GLfloat deltaTime, bool keys[], glm::vec3 _front)
{
	GLfloat cameraSpeed = speed * deltaTime;
	if (keys[GLFW_KEY_W])
		position += cameraSpeed * front;
	if (keys[GLFW_KEY_S])
		position -= cameraSpeed * front;
	if (keys[GLFW_KEY_A])
		position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
	if (keys[GLFW_KEY_D])
		position += glm::normalize(glm::cross(front, up)) * cameraSpeed;

	front = glm::normalize(_front);
}

const float * Camera::GetView()
{
	view = glm::lookAt(position, position + front, up);
	return glm::value_ptr(view);	
}

const float * Camera::GetProjection()
{
	projection = glm::perspective(45.0f, (float)screenWidth / screenHeight, 0.1f, 100.0f);
	return glm::value_ptr(projection);
}

Camera::~Camera()
{
}
