#include <iostream>
#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "./src/utils/functions/functions.h"

using namespace std;

int main(int argc, char *argv[]) {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};
	int windowWidth;
	int windowHeight;
	utilsFunctions::checkMainCommandArgs(argc, argv, windowWidth, windowHeight);
	GLFWwindow *window {utilsFunctions::initGLFW(windowWidth, windowHeight)};
	utilsFunctions::initGLAD(windowWidth, windowHeight);

	// send input vertex data to the GPU and determine how it should process the data within a vertex and fragment shader
	// then link both shader objects into a shader program we can use for rendering
	unsigned int vertexShaderId {utilsFunctions::initVertexShader()};
	unsigned int fragmentShaderId {utilsFunctions::initFragmentShader()};
	unsigned int shaderProgramId {utilsFunctions::initAndLinkShaderProgram(vertexShaderId, fragmentShaderId)};
	unsigned int vertexArrayObjectId {utilsFunctions::linkVertexAttributes(vertices, sizeof(vertices))};

	// render loop
	// 1 iteration == 1 frame
    while (!glfwWindowShouldClose(window)) {
		utilsFunctions::processInput(window);
		utilsFunctions::setBackground(0.0f, 0.5f, 0.5f, 1.0f);

		//glUseProgram(shaderProgramId);
		glBindVertexArray(vertexArrayObjectId);
		glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}