#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

namespace utilsFunctions {
	void checkMainCommandArgs(int argc, char *argv[], int &windowWidth, int &windowHeight);
	GLFWwindow *initGLFW(const int width, const int height);
	void initGLAD(const int width, const int height);
	unsigned int initVertexShader();
	unsigned int initFragmentShader();
	unsigned int initAndLinkShaderProgram(unsigned int vertexShaderId, unsigned int fragmentShaderId);
	unsigned int linkVertexAttributes(float *vertices, size_t verticesSize);
	void processInput(GLFWwindow *window);
	void processWindowSizeChange(GLFWwindow *window, int width, int height);
	void setBackground(float r, float g, float b, float a);
}

#endif