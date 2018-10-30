// GLEW
#define GLEW_STATIC
#include "..\3rdParty\GL\glew.h"
// GLFW
#include "..\3rdParty\GLFW\glfw3.h"

#include <iostream>

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

	return 0;
}