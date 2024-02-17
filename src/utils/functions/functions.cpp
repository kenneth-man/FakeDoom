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

GLFWwindow *utilsFunctions::initGLFW(
	const int width,
	const int height
) {
	// Check GLFW initializes correctly
    if (!glfwInit()) {
		cerr << "Failed to initialize GLFW";
        glfwTerminate();
        exit(1);
    }

    GLFWwindow *window = glfwCreateWindow(width, height, "FakeDOOM", NULL, NULL);

    if (!window) {
		cerr << "Failed to initialize GLFW Window";
        glfwTerminate();
        exit(1);
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
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
		cerr << "Failed to initialize GLAD";
        glfwTerminate();
        exit(1);
    }

	glViewport(0, 0, width, height);
}

unsigned int utilsFunctions::initVertexShader() {
	// simple vertex shader in GLSL (OpenGL Shading Language); stored in C string
	const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
	
	// shader object id
	unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

	// attach the shader source code to the shader object and compile the shader
	glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShaderId);

	// check if compilation was successful after the call to `glCompileShader`
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		cerr << "Vertex shader compilation failed\n" << infoLog;
		exit(1);
	}

	return vertexShaderId;
}

unsigned int utilsFunctions::initFragmentShader() {
	const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
	
	unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShaderId);

	// check if compilation was successful after the call to `glCompileShader`
	int success;
	char infoLog[512];
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
        cerr << "Fragment shader compilation failed\n" << infoLog;
		exit(1);
    }

	return fragmentShaderId;
}

unsigned int utilsFunctions::initAndLinkShaderProgram(
	unsigned int vertexShaderId,
	unsigned int fragmentShaderId
) {
	unsigned int shaderProgramId = glCreateProgram();

	// link vertex and fragment shaders to a shader program object
	// linking the outputs of each shader to the inputs of the next shader
	glAttachShader(shaderProgramId, vertexShaderId);
	glAttachShader(shaderProgramId, fragmentShaderId);
	glLinkProgram(shaderProgramId);

	int success;
    char infoLog[512];
	glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);
		cerr << "Shader Program compilation failed\n" << infoLog;
		exit(1);
	}

	// Every shader and rendering call after glUseProgram will now use this program object and it's shaders
	glUseProgram(shaderProgramId);

	// cleanup shader objects; no longer need them anymore
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	return shaderProgramId;
}

unsigned int utilsFunctions::linkVertexAttributes(
	// when you pass an array, you're passing a pointer/memory address to its first element (since true C arrays don't exist)
	// meaning you're not actually passing the entire array
	float *vertices,
	size_t verticesSize
) {
	unsigned int vertexBufferObjectId, vertextArrayObjectId;
    glGenVertexArrays(1, &vertextArrayObjectId);
    glGenBuffers(1, &vertexBufferObjectId);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s)
    glBindVertexArray(vertextArrayObjectId);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

	// uncomment this call to draw in wireframe polygons
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	return vertextArrayObjectId;
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
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays
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