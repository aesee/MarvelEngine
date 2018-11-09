#pragma once
#include "stdafx.h"
#include "Camera.h"
#include "Shader.h"

class Object
{
protected:
	GLfloat * obj;	// coordinates
	GLuint VAO;		// array buffer
	GLuint textures[10];	// array of textures; i think 10 will be enough for now
	GLuint currentTexture = 0;	// just indexer for LoadTexture method
	Shader* shader;		// Shader for this object
	glm::mat4 model;	// Model to translate, scale and rotate

	Object(GLuint VBO);
	void LoadObjectIntoBuffer(GLuint nPoints);

public:
	void Draw();
	void LoadTexture(const char * name);
	void virtual UseShader(Camera* camera);
	void virtual SetLocation(glm::vec3 location);

	virtual ~Object();
};

class Cube : public Object
{
public:
	Cube(GLuint VBO);
	~Cube();

	void UseShader(Camera* camera) override;

	/*void SetLocation(glm::vec3 location) override
	{
		static int i = 0;
		Object::SetLocation(location);

		GLfloat angle = 20.0f * i;
		model = glm::rotate(model, angle + (GLfloat)glfwGetTime() * 50.0f, glm::vec3(1.0f, 0.3f, 0.5f));
		glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		i++;
	}*/
};

class Floor : public Object
{
public:
	Floor(GLuint VBO) : Object(VBO)
	{
		GLuint nElements = 9;
		obj = new GLfloat[nElements]{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
		};
		shader = new Shader("shaders\\shader.vert", "shaders\\shader.frag");
		LoadObjectIntoBuffer(nElements);
	}
	~Floor() {}

	void UseShader(Camera* camera) override
	{
		Object::UseShader(camera);
		glUniform1i(glGetUniformLocation(shader->Program, "ourTexture1"), 1);
		glUniform1i(glGetUniformLocation(shader->Program, "ourTexture2"), 0);
	}

	void SetLocation(glm::vec3 location) override
	{
		Object::SetLocation(location);
		model = glm::rotate(model, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	}
};
