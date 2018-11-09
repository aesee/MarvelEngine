#include "stdafx.h"
#include "Object.h"


Object::Object(GLuint VBO)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);	// Bind array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// Copy vertex buffer	

	// Interpret vertex data
	// layout (location = 0), vec3, float points, don't need to normalize, step in 3 (x,y,z), offset 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);*/
	// Texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);	// Disconnect array
}


void Object::LoadObjectIntoBuffer(GLuint nPoints)
{
	glBufferData(GL_ARRAY_BUFFER, nPoints * sizeof(GLfloat), obj, GL_STATIC_DRAW);
}

Object::~Object()
{
	delete obj;
	delete shader;
}

void Object::Draw()
{
	glBindVertexArray(VAO);
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);	// Need to change count to variables !
	glBindVertexArray(0);
}

void Object::LoadTexture(const char * name)
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

void Object::UseShader(Camera* camera)
{
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, false, camera->GetView());
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, false, camera->GetProjection());
}

void Object::SetLocation(glm::vec3 location)
{
	model = glm::translate(glm::mat4(1.0f), location);
}

Cube::Cube(GLuint VBO) : Object(VBO)
{
	GLuint nElements = 180;

	obj = new GLfloat[nElements]{
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	shader = new Shader("shaders\\shader.vert", "shaders\\shader.frag");
	
	LoadObjectIntoBuffer(nElements);
}

Cube::~Cube()
{
}

void Cube::UseShader(Camera* camera)
{
	Object::UseShader(camera);
	glUniform1i(glGetUniformLocation(shader->Program, "ourTexture1"), 1);
	glUniform1i(glGetUniformLocation(shader->Program, "ourTexture2"), 0);
}
