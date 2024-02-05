#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

namespace utilsFunctions {
	void checkMainCommandArgs(int argc, char *argv[], int &windowWidth, int &windowHeight);
	GLFWwindow* initGLFW(const int width, const int height);
	void initGLAD(const int width, const int height);
	void processInput(GLFWwindow *window);
	void setBackground(float r, float g, float b, float a);
}

#endif