#pragma once

#include <fstream>
#include <iterator>

std::string readFile(const char* filepath)
{
	std::ifstream myFile(filepath);
	std::string content((std::istreambuf_iterator<char>(myFile)), std::istreambuf_iterator<char>());

	return content;
}

void DrawOnlyWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void DrawAllPolygons()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}