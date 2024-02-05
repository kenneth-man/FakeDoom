#include <iostream>
#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "./src/utils/functions/functions.h"

using namespace std;

int main(int argc, char *argv[]) {
	int windowWidth;
	int windowHeight;
	utilsFunctions::checkMainCommandArgs(argc, argv, windowWidth, windowHeight);
	GLFWwindow *window {utilsFunctions::initGLFW(windowWidth, windowHeight)};
	utilsFunctions::initGLAD(windowWidth, windowHeight);

	// render loop
	// 1 iteration == 1 frame
    while (!glfwWindowShouldClose(window)) {
		utilsFunctions::processInput(window);

		utilsFunctions::setBackground(0.0f, 0.5f, 0.5f, 1.0f);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}