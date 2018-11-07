#pragma once

// GLEW
//#define GLEW_STATIC
#pragma comment (lib, "glew32.lib")	// Have problem with static library so I use dynamic
#include "..\3rdParty\GL\glew.h"
// GLFW
#include "..\3rdParty\GLFW\glfw3.h"
// Simple OpenGL Image Loader
#pragma comment (lib, "SOIL.lib")
#include "..\3rdParty\SOIL\SOIL.h"

#include <iostream>
#include <string>

#include <fstream>
#include <iterator>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>