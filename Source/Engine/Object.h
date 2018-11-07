#pragma once
class Object
{
protected:
	GLfloat * obj;
	int nElements;
	GLuint textures[10];
	GLuint currentTexture = 0;

public:
	Object();
	virtual ~Object();

	void Draw()
	{
		glDrawArrays(GL_TRIANGLES, 0, 36);
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
};

class Cube : public Object
{
public:
	Cube();
	~Cube();
};
