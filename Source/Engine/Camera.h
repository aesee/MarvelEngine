#pragma once
#include "stdafx.h"

class Camera
{
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 direction;	
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 front;
	GLint screenWidth;
	GLint screenHeight;
	GLfloat speed = 5.0f;

	glm::highp_mat4 view;
	glm::highp_mat4 projection;

public:
	Camera(int with, int height);
	void Control(GLfloat deltaTime, bool keys[], glm::vec3 _front);
	const float * GetView();
	const float * GetProjection();
	~Camera();
};

