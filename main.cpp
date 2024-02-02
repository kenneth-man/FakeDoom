#include <iostream>
#include <algorithm>
#include "./external/glad/glad/glad.h"
#include <GLFW/glfw3.h>

int main(void)
{
	// Testing if CMake is using C++ 17
	std::cout << "Using C++17: " << std::clamp(42, -1, 1) << std::endl;

     // Check GLFW initializes correctly
    if (!glfwInit()) {
       	fprintf(stderr, "Failed to initialize GLFW\n");
        glfwTerminate();
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Simple GLFW Window", NULL, NULL);

    if (!window) {
		fprintf(stderr, "Failed to initialize GLFW Window\n");
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

	// Check GLAD initializes correctly
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        glfwTerminate();
        return -1;
    }


    while (!glfwWindowShouldClose(window)) {
        // Render here (you can add your rendering code here)

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up
    glfwTerminate();

    return 0;
}