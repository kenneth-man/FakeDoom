#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include <iostream>
#include <string>
#include "../../../external/glad/glad/glad.h"
#include "../../../external/glfw/include/GLFW/glfw3.h" // <GLFW/glfw3.h>

using namespace std;

namespace utilsFunctions {
	void checkMainCommandArgs(int argc, char *argv[], int &windowWidth, int &windowHeight);
	GLFWwindow* initGLFW(const int width, const int height);
	void initGLAD(const int width, const int height);
}

#endif