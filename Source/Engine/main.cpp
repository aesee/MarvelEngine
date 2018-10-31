// GLEW
//#define GLEW_STATIC
#pragma comment (lib, "glew32.lib")	// Have problem with static library so I use dynamic
#include "..\3rdParty\GL\glew.h"
// GLFW
#include "..\3rdParty\GLFW\glfw3.h"

#include <iostream>
#include <string>

// GLFW callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int node)
{
	// Close the window once escape is pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

int main()
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
	int width = 800;
	int height = 600;
	GLFWwindow* window = glfwCreateWindow(width, height, "Marvel Engine", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create a window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Init GLEW
	glewExperimental = GL_TRUE;	// Using an experimental features
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Set viewport
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Set condition of closing window by escape button
	glfwSetKeyCallback(window, key_callback);


	
	
	
	// Giant shaders config code
	/*GLfloat vertices[] = {								// Simple triangle
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};*/

	GLfloat vertices[] = {								// Simple rectangle
	 0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f 
	};
	GLuint indices[] = {
		0, 1, 3,   // First triangle
		1, 2, 3    // Second triangle
	};

	GLuint EBO;											// Create element buffer
	glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);			// And bind it
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	GLuint VBO;											// Create vertex buffer object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);					// Bind vbo to our buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// Copy vertices to buffer; the data won't change

	// Simple vertex shader
	std::string vShader = "#version 330 core\nlayout (location = 0) in vec3 position;\nvoid main()\n{\ngl_Position = vec4(position.x, position.y, position.z, 1.0);\n}"; // read a string with the file contents
	GLchar const* vertexShaderSource = vShader.c_str();

	// Create vertex shader
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Simple fragment shader
	std::string fShader = "#version 330 core\nout vec4 color;\nvoid main()\n{\ncolor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n}";
	GLchar const* fragmentShaderSource = fShader.c_str();

	// Create fragment shader
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Test result of shader's building is success
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Create shader program
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	// Attach shader to the program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check there's no error
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Remove shaders that don't need anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Interpret vertex data
	// layout (location = 0), vec3, float points, don't need to normalize, step in 3 (x,y,z), offset 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Create vertex array
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);	// Bind array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// Copy vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);	// Copy indices of element
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);	// Set pointers on vertex attributes
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);	// Unconnect array

	// Draw only wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Game Loop
	while (!glfwWindowShouldClose(window))
	{
		// Check input
		glfwPollEvents();

		// Clear screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw frame
		glUseProgram(shaderProgram);		// Using shader program
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);	// OpenGl function that draw an object
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		// Swap buffer; we use a double buffering
		glfwSwapBuffers(window);
	}
	
	// Clear resources before end
	glfwTerminate();

	return 0;
}