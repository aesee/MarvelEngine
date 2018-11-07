#include "stdafx.h"
#include "Shader.h"

// GLFW callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int node)
{
	// Close the window once escape is pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

GLFWwindow* WindowInit(int width, int height)
{
	// Init GLFW
	glfwInit();
	// Set a require versions of opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Set profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Not allow to resize window
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a window
	GLFWwindow* window = glfwCreateWindow(width, height, "Marvel Engine", nullptr, nullptr);
	if (window == nullptr)
	{
		//std::cout << "Failed to create a window" << std::endl;
		glfwTerminate();
		//return -1;
		throw std::string("Failed to create a window");
	}
	glfwMakeContextCurrent(window);

	// Init GLEW
	glewExperimental = GL_TRUE;	// Using an experimental features
	if (glewInit() != GLEW_OK)
	{
		//std::cout << "Failed to initialize GLEW" << std::endl;
		//return -1;
		throw std::string("Failed to initialize GLEW");
	}

	// Set viewport
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Set condition of closing window by escape button
	glfwSetKeyCallback(window, key_callback);

	return window;
}

int main()
{
	GLFWwindow* window = WindowInit(800, 600);

	// Check how many shader vertexes we can process
	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
		
	// Giant shaders config code
	/*GLfloat vertices[] = {
		// Positions         // Colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f 
	};*/

	GLfloat vertices[] = {
		// Positions          // Colors           // Texture coordinates
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f 
	};
	GLuint indices[] = {
		0, 1, 3,   // First triangle
		1, 2, 3    // Second triangle
	};

	GLuint IBO;											// Create index buffer
	glGenBuffers(1, &IBO);
	
	GLuint VBO;											// Create vertex buffer object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);					// Bind vbo to our buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// Copy vertices to buffer; the data won't change

	Shader generalShader("shaders\\shader.vert", "shaders\\shader.frag");

	// Create vertex array
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);	// Bind array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// Copy vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);	// Copy indices of element
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Interpret vertex data
	// layout (location = 0), vec3, float points, don't need to normalize, step in 3 (x,y,z), offset 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);	// Disconnect array

	// Generate texture for OpenGL
	GLuint texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// Load texture
	int width, height;
	unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	// Attach loaded image and generate mipmap
	// GLBorder always need to be zero
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Another texture
	GLuint texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// Load texture
	image = SOIL_load_image("sample.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	// Attach loaded image and generate mipmap
	// GLBorder always need to be zero
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free memory
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Game Loop
	while (!glfwWindowShouldClose(window))
	{
		// Check input
		glfwPollEvents();

		// Clear screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw frame
		//glUniform1f(glGetUniformLocation(generalShader.Program, "offset"), 0.5f);
		generalShader.Use();				// Using shader program
		// Update uniform color in shaders
		//GLfloat timeValue = (GLfloat) glfwGetTime();
		//GLfloat greenValue = (GLfloat) (sin(timeValue) / 2) + 0.5;

		// Some experiment with matrixes
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0, 0.0, 1.0));
		//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
		GLuint transformLoc = glGetUniformLocation(generalShader.Program, "transform");
		glUniformMatrix4fv(transformLoc, 1, false, glm::value_ptr(trans));
		//glUniform1f(glGetUniformLocation(generalShader.Program, "newColor"), 1.0f);
		//GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "newColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		// Draw object
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);	// OpenGl function that draw an object
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(generalShader.Program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(generalShader.Program, "ourTexture2"), 1);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		// Swap buffer; we use a double buffering
		glfwSwapBuffers(window);
	}
	
	// Clear resources before end
	glfwTerminate();

	return 0;
}