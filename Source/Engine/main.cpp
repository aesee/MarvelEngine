#include "stdafx.h"
#include "Shader.h"
#include "Camera.h"
#include "Object.h"

int screenWidth = 1280;
int screenHeight = 720;
bool keys[1024];
GLfloat lastX = screenWidth / 2, lastY = screenHeight / 2;
GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
bool firstMouse = true;
glm::vec3 mouse = glm::vec3(0.0f, 0.0f, -1.0f);;

// GLFW callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int node)
{
	// Close the window once escape is pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	// Camera control
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	GLfloat sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	mouse.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	mouse.y = sin(glm::radians(pitch));
	mouse.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
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

	// Enable depth check
	glEnable(GL_DEPTH_TEST);

	// Init GLEW
	glewExperimental = GL_TRUE;	// Using an experimental features
	if (glewInit() != GLEW_OK)
	{
		throw std::string("Failed to initialize GLEW");
	}

	// Set viewport
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Set condition of closing window by escape button
	glfwSetKeyCallback(window, key_callback);

	// Get mouse cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set mouse control
	glfwSetCursorPosCallback(window, mouse_callback);
	lastX = width / 2; lastY = height / 2;

	// Check how many shader vertices we can process
	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	return window;
}

int main()
{
	GLFWwindow* window = WindowInit(screenWidth, screenHeight);
	Camera* camera = new Camera(screenWidth, screenHeight);
		
	// Cube
	Cube* cube = new Cube();

	GLuint IBO;											// Create index buffer
	glGenBuffers(1, &IBO);
	
	GLuint VBO;											// Create vertex buffer object
	glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);					// Bind vbo to our buffer
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// Copy vertices to buffer; the data won't change

	//Shader generalShader("shaders\\shader.vert", "shaders\\shader.frag");

	// Create vertex array
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);	// Bind array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// Copy vertex buffer
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	cube->AddIntoBuffer();

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

	// Generate texture for OpenGL
	cube->LoadTexture("container.jpg");
	cube->LoadTexture("sample.jpg");

	glBindTexture(GL_TEXTURE_2D, 0);

	// Time counter
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	// Positions for drawing a 10 cubes
	glm::vec3 cubePositions[] = {
		  glm::vec3(0.0f,  0.0f,  0.0f),
		  glm::vec3(2.0f,  5.0f, -15.0f),
		  glm::vec3(-1.5f, -2.2f, -2.5f),
		  glm::vec3(-3.8f, -2.0f, -12.3f),
		  glm::vec3(2.4f, -0.4f, -3.5f),
		  glm::vec3(-1.7f,  3.0f, -7.5f),
		  glm::vec3(1.3f, -2.0f, -2.5f),
		  glm::vec3(1.5f,  2.0f, -2.5f),
		  glm::vec3(1.5f,  0.2f, -1.5f),
		  glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	// Game Loop
	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check input
		glfwPollEvents();
		// Camera control
		camera->Control(deltaTime, keys, mouse);
		
		// Sky color
		glClearColor(0.52f, 0.8f, 0.92f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Draw frame
		// Translate to shader
		cube->UseShader(camera);
		glBindVertexArray(VAO);
		GLuint count = sizeof(cubePositions) / (cubePositions->length() * sizeof(float));
		for (GLuint i = 0; i < count; i++)
		{
			cube->SetLocation(cubePositions[i]);
			cube->Draw();
		}
		//cube->SetLocation(glm::vec3(0,0,0));
		//cube->Draw();
		glBindVertexArray(0);

		// Swap buffer; we use a double buffering
		glfwSwapBuffers(window);
	}
	
	// Clear resources before end
	glfwTerminate();

	return 0;
}