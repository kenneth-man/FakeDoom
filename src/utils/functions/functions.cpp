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

// A shader is a program that runs on your GPU; we can create a vertext, geometry and fragment shader to override GPU defaults (or they may not exist)
// These shaders are compiled, linked and run on our GPU `glCompileShader`, whilst our C++ program runs on our CPU
// Vertex shader = transforms each vertex's 3D position in virtual space to the 2D coordinate on the screen (in a window)
	// and gets called for each vertex that is rendered
unsigned int utilsFunctions::initVertexShader() {
	// Simple vertex shader in GLSL (OpenGL Shading Language); stored in C string
	const char *vertexShaderSource {"#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0"};
	
	// Shader object id
	unsigned int vertexShaderId {glCreateShader(GL_VERTEX_SHADER)};

	// Attach the shader source code to the shader object and compile the shader
	glShaderSource(vertexShaderId, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShaderId);

	// Check if compilation was successful after the call to `glCompileShader`
	utilsFunctions::handleShaderCompileError(vertexShaderId, "Vertex shader compilation failed");

	return vertexShaderId;
}

// Fragment (pixel) shader = defines RGBA (red, green, blue, alpha) colors for each pixel being processed
	// and gets called for each pixel that needs to get rasterized (process of drawing to screen, where a window is just a pixel array)
unsigned int utilsFunctions::initFragmentShader() {
	const char *fragmentShaderSource {"#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0"};
	
	unsigned int fragmentShaderId {glCreateShader(GL_FRAGMENT_SHADER)};

	glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShaderId);

	utilsFunctions::handleShaderCompileError(fragmentShaderId, "Fragment shader compilation failed");

	return fragmentShaderId;
}

unsigned int utilsFunctions::initAndLinkShaderProgram(
	unsigned int vertexShaderId,
	unsigned int fragmentShaderId
) {
	unsigned int shaderProgramId {glCreateProgram()};

	// Link vertex and fragment shaders to a shader program object
	// Linking the outputs of each shader to the inputs of the next shader
	glAttachShader(shaderProgramId, vertexShaderId);
	glAttachShader(shaderProgramId, fragmentShaderId);
	glLinkProgram(shaderProgramId);

	utilsFunctions::handleShaderProgramLinkError(shaderProgramId, "Shader Program compilation failed");

	// Every shader and rendering call after glUseProgram will now use this program object and it's shaders
	glUseProgram(shaderProgramId);

	// Cleanup shader objects; no longer need them anymore
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	return shaderProgramId;
}

unsigned int utilsFunctions::linkVertexAttributes(
	// When you pass an array, you're passing a pointer/memory address to its first element (since true C arrays don't exist)
	// Meaning you're not actually passing the entire array; so the argument decays into a pointer to its first element
	float *vertices,
	size_t verticesSize,
	unsigned int *indices,
	size_t indicesSize
) {
	unsigned int vaoId, vboId, eboId;

	// VAOs (stored in CPU memory); tells OpenGL how to find and use vertex data in VBOs (vertex buffers) when rendering
	// VBOs (stored in GPU memory, so prevents GPU-CPU communication bottleneck, improve efficiency) stores the actual vertex data attributes (positions, normals, texture coords...)
	// `glVertexAttribPointer` links a VAO with the currently bound VBO
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

	// Use generated VBO buffer and insert data into it with same size as `verticesSize`
    glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

	// Defining we want position (vertex attribute) coordinates to be at index 0, and how opengl should interpret what consitutes as a vertex from our buffer data in `glBufferData`
	// 5th arg is `stride` which is the amount of bytes between each vertex (size of each vertex); so that opengl knows how many bytes to jump in the buffer to the next vertex
	// 6th arg is `pointer` which is the offset in bytes of the attributes in a vertex; e.g. A single vertex may have attributes: position, texture coordinate, normal
		// `pointer` is the offset of those in bytes in the buffer; e.g. position (offset is 0 since it's first), texture coordinate (12 bytes forward/offset), normal (20 bytes)...
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	// Use generated EBO (index) buffer and insert data into it with same size as `indicesSize`
	// EBO buffers allow us to re-use existing vertices, limiting amount of GPU needed (duplicate vertices require more memory)
	// EBO buffers must be made up of unsigned integers
	glGenBuffers(1, &eboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW); 

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