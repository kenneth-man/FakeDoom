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

unsigned int utilsFunctions::linkVertexAttributes() {
	unsigned int vaoId;

	// VAOs (stored in CPU memory); tells OpenGL how to find and use vertex data in VBOs (vertex buffers) when rendering
	// VBOs (stored in GPU memory, so prevents GPU-CPU communication bottleneck, improve efficiency) stores the actual vertex data attributes (positions, normals, texture coords...)
	// `glVertexAttribPointer` links a VAO with the currently bound VBO
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

	// Defining we want position (vertex attribute) coordinates to be at index 0, and how opengl should interpret what consitutes as a vertex from our buffer data in `glBufferData`
	// 5th arg is `stride` which is the amount of bytes between each vertex (size of each vertex); so that opengl knows how many bytes to jump in the buffer to the next vertex
	// 6th arg is `pointer` which is the offset in bytes of the attributes in a vertex; e.g. A single vertex may have attributes: position, texture coordinate, normal
		// `pointer` is the offset of those in bytes in the buffer; e.g. position (offset is 0 since it's first), texture coordinate (12 bytes forward/offset), normal (20 bytes)...
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	// Uncomment this call to draw in wireframe polygons
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	return vaoId;
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

void utilsFunctions::setBackground(
	float r,
	float g,
	float b,
	float a
) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
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