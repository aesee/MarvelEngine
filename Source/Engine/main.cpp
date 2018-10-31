// GLEW
//#define GLEW_STATIC
#pragma comment (lib, "glew32.lib")	// Have problem with static library so I use dynamic
#include "..\3rdParty\GL\glew.h"
// GLFW
#include "..\3rdParty\GLFW\glfw3.h"

#include <iostream>

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

	// Game Loop
	while (!glfwWindowShouldClose(window))
	{
		// Check input
		glfwPollEvents();

		// Draw a frame
		// Clear screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap buffer; we use a double buffering
		glfwSwapBuffers(window);
	}
	
	// Clear resources before end
	glfwTerminate();

	return 0;
}