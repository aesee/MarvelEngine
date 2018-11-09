#pragma once
#include "stdafx.h"
#include "Camera.h"
#include "Shader.h"

class Object
{
protected:
	GLfloat * obj;
	int nElements;
	GLuint textures[10];
	GLuint currentTexture = 0;
	Shader* shader;
	glm::mat4 model;

public:
	Object();
	virtual ~Object();

	void Draw()
	{
		glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);	// Need to change count to variables
	}

	void LoadTexture(const char * name)
	{
		glGenTextures(1, textures + currentTexture * sizeof(GLuint));
		//glBindTexture(GL_TEXTURE_2D, textures[currentTexture]);
		// Load texture
		int width, height;
		unsigned char* image = SOIL_load_image(name, &width, &height, 0, SOIL_LOAD_RGB);
		// Attach loaded image and generate mipmap
		// GLBorder always need to be zero
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		glActiveTexture(GL_TEXTURE0 + currentTexture);
		glBindTexture(GL_TEXTURE_2D, textures[currentTexture]);

		if (currentTexture < 9)
		{
			currentTexture += 1;
		}

		// Free memory
		SOIL_free_image_data(image);
	}

	void AddIntoBuffer()
	{
		glBufferData(GL_ARRAY_BUFFER, nElements * sizeof(GLfloat), obj, GL_STATIC_DRAW);
	}

	void virtual UseShader(Camera* camera)
	{
		glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, false, camera->GetView());
		glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, false, camera->GetProjection());
	}

	void virtual SetLocation(glm::vec3 location)
	{
		//model = glm::translate(model, location);
		model = glm::translate(glm::mat4(1.0f), location);
	}
};

class Cube : public Object
{
public:
	Cube();
	~Cube();

	void UseShader(Camera* camera) override
	{
		Object::UseShader(camera);
		glUniform1i(glGetUniformLocation(shader->Program, "ourTexture1"), 1);
		glUniform1i(glGetUniformLocation(shader->Program, "ourTexture2"), 0);
	}

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
