#include <iostream>
#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "./src/utils/functions/functions.h"

using namespace std;

int main(int argc, char *argv[]) {
	float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
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

	// send input vertex data to the GPU and determine how it should process the data within a vertex and fragment shader
	// vertex shaders transform shape positions into 3D drawing coordinates; fragment shaders compute the renderings of a shape's colors and other attributes
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

		//glUseProgram(shaderProgramId);
		glBindVertexArray(vaoId);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll IO events (keys pressed/released, mouse moved etc.)
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}