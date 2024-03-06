#include "functions.h"

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

	utilsFunctions::handleError("Add both window width and height arguments to the command", false);
}

GLFWwindow *utilsFunctions::initGLFW(
	const int width,
	const int height
) {
	// Check GLFW initializes correctly
    if (!glfwInit()) {
		utilsFunctions::handleError("Failed to initialize GLFW");
    }

	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window {glfwCreateWindow(width, height, "FakeDOOM", nullptr, nullptr)};

    if (!window) {
		utilsFunctions::handleError("Failed to initialize GLFW Window");
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

	// The number of screen updates to wait from the time glfwSwapBuffers was called before swapping the buffers and returning.
	// This is sometimes called vertical synchronization, vertical retrace synchronization or just vsync
	glfwSwapInterval(1);

	glfwSetFramebufferSizeCallback(window, processWindowSizeChange);

	return window;
}

void utilsFunctions::initGLAD(
	const int width,
	const int height
) {
	// Check GLAD initializes correctly
	// GLAD manages function pointers for OpenGL so we want to initialize GLAD before we call any OpenGL function
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		utilsFunctions::handleError("Failed to initialize GLAD");
    }

	glViewport(0, 0, width, height);
}

void utilsFunctions::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	} 
}

void utilsFunctions::processWindowSizeChange(
	GLFWwindow *window,
	int width,
	int height
) {
    // Make sure the viewport matches the new window dimensions; note that width and 
    // Height will be significantly larger than specified on retina displays
    glViewport(0, 0, width, height);
}

void utilsFunctions::handleError(
	string message,
	bool shouldGlfwTerminate
) {
	cerr << message;
	if (shouldGlfwTerminate) {
		glfwTerminate();
	}
	exit(1);
}

// `iv` = integer vector
void utilsFunctions::handleShaderCompileError(
	unsigned int shaderId,
	string message
) {
	int success;
	char infoLog[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
		cerr << message << '\n' << infoLog;
		exit(1);
	}
}

void utilsFunctions::handleShaderProgramLinkError(
	unsigned int shaderProgramId,
	string message
) {
	int success;
    char infoLog[512];
	glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderProgramId, 512, nullptr, infoLog);
		cerr << message << '\n' << infoLog;
		exit(1);
	}
};