#pragma once

// GLEW
//#define GLEW_STATIC
#pragma comment (lib, "glew32.lib")	// Have problem with static library so I use dynamic
#include "..\3rdParty\GL\glew.h"
// GLFW
#include "..\3rdParty\GLFW\glfw3.h"

#include <iostream>
#include <string>

#include <fstream>
#include <iterator>