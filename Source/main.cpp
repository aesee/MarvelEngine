// Import libraries in Visual Studio
#pragma comment(lib, "../Lib/glew32.lib")
#pragma comment(lib, "../Lib/glfw3.lib")

#include <stdio.h>
#include <stdlib.h>

#include "3rdParty/GLEW/glew.h"
#include "3rdParty/GLFW/glfw3.h"

#include "3rdParty/glm/glm.hpp"
using namespace glm;

int main() 
{
	if (!glfwInit())
	{
		fprintf(stderr, "Error in GLFWn initialization");
		return -1;
	}
	
	//glfwWindowHint(GLFW_SAMPLES, 1);			// Anti-aliasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	// OpenGL version: 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Forbid the old opengl

	// Create window
	GLFWwindow* window;
	window = glfwCreateWindow(1024, 768, "Tutorial 01", nullptr, nullptr);
	if (window == NULL) 
	{
		fprintf(stderr, "Can't create a window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// GLEW init
	glewExperimental = true;
	if (glewInit() != GLEW_OK) 
	{
		fprintf(stderr, "Can't init GLEWn");
		return -1;
	}

	// Check input
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do 
	{
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	// Close window on escape key
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}