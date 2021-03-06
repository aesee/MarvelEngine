// Import libraries in Visual Studio
#pragma comment(lib, "../Lib/glew32.lib")
#pragma comment(lib, "../Lib/glfw3.lib")
#pragma comment( lib, "OpenGL32.lib" )

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
	window = glfwCreateWindow(1024, 768, "Marvel Engine", nullptr, nullptr);
	if (window == NULL) 
	{
		fprintf(stderr, "Can't create a window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Create VAO
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] = 
	{
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};


	GLuint vertexbuffer;						 // Buffer's ID
	glGenBuffers(1, &vertexbuffer); 			 // Create 1 buffer	
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); // Make the buffer current
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);		// Pass triangle data to OpenGL

	// Main loop
	do 
	{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// Vertex are first attribute
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // Attribute 0 
			3,                  // Size
			GL_FLOAT,           // Type
			GL_FALSE,           // Values are not normalize
			0,                  // Step
			(void*)0            // Array's offset
		);

		// Display triangle
		glDrawArrays(GL_TRIANGLES, 0, 3); // Vertex from 0 to 3
		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	// Close window on escape key
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	//glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}