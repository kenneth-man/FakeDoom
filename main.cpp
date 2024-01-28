#include <iostream>
#include <GLFW/glfw3.h>

// int main() {
// 	if (!glfwInit()) {
// 		std::cout << "glfw failed" << std::endl;
// 		return 1;
// 	}
// 	std::cout << "main test" << std::endl;
// 	return 0;
// }

int main(void)
{
     // Initialize GLFW
    if (!glfwInit()) {
        // Handle initialization failure
        return -1;
    }
// Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "Simple GLFW Window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Loop until the user closes the window
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