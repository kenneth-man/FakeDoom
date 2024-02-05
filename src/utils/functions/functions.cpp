#include "./functions.h"

void utilsFunctions::checkMainCommandArgs(
	int argc,
	char *argv[],
	int &windowWidth,
	int &windowHeight
) {
	if (argc == 1) {
		windowWidth = 800;
		windowHeight = 600;
		return;
	}

	if (argc == 3) {
		windowWidth = stoi(argv[1]);
		windowHeight = stoi(argv[2]);
		return;
	}

	cerr << "Add both window width and height arguments to the command";
	exit(1);
}

GLFWwindow* utilsFunctions::initGLFW(const int width, const int height) {
	// Check GLFW initializes correctly
    if (!glfwInit()) {
		cerr << "Failed to initialize GLFW";
        glfwTerminate();
        exit(1);
    }

    GLFWwindow* window = glfwCreateWindow(width, height, "FakeDOOM", NULL, NULL);

    if (!window) {
		cerr << "Failed to initialize GLFW Window";
        glfwTerminate();
        exit(1);
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

	return window;
}

void utilsFunctions::initGLAD(const int width, const int height) {
	// Check GLAD initializes correctly
	// GLAD manages function pointers for OpenGL so we want to initialize GLAD before we call any OpenGL function
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cerr << "Failed to initialize GLAD";
        glfwTerminate();
        exit(1);
    }

	glViewport(0, 0, width, height);
}

void utilsFunctions::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	} 
}

void utilsFunctions::setBackground(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}