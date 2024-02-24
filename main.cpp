#include <iostream>
#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "./src/utils/functions/functions.h"

using namespace std;

int main(int argc, char *argv[]) {
	float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right vertex
         0.5f, -0.5f, 0.0f,  // bottom right vertex
        -0.5f, -0.5f, 0.0f,  // bottom left vertex
        -0.5f,  0.5f, 0.0f   // top left vertex
    };
    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
	int windowWidth;
	int windowHeight;

	utilsFunctions::checkMainCommandArgs(argc, argv, windowWidth, windowHeight);
	GLFWwindow *window {utilsFunctions::initGLFW(windowWidth, windowHeight)};
	utilsFunctions::initGLAD(windowWidth, windowHeight);
	unsigned int vertexShaderId {utilsFunctions::initVertexShader()};
	unsigned int fragmentShaderId {utilsFunctions::initFragmentShader()};
	// link both shader objects into a shader program we can use for rendering
	unsigned int shaderProgramId {utilsFunctions::initAndLinkShaderProgram(vertexShaderId, fragmentShaderId)};
	// telling OpenGL how it should interpret the vertex data in memory and how it should connect the vertex data to the vertex shader's attributes
	unsigned int vaoId {utilsFunctions::linkVertexAttributes(vertices, sizeof(vertices), indices, sizeof(indices))};

	// render loop
	// 1 iteration == 1 frame
    while (!glfwWindowShouldClose(window)) {
		utilsFunctions::processInput(window);
		utilsFunctions::setBackground(0.0f, 0.5f, 0.5f, 1.0f);

		glBindVertexArray(vaoId);
		// if no EBO buffer (aka index buffer), use glDrawArrays(GL_TRIANGLES, 0, 3);
		// draws the currently bound buffer
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll IO events (keys pressed/released, mouse moved etc.)
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}