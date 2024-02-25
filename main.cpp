#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <string>
#include "./src/utils/functions/functions.h"

// Macro to wrap an opengl function call to check and log errors
// `#x` converts `x` to a string
// `\` allows you to line break onto seperate lines
#define gLCall(x) glClearError();\
	x;\
	glLogError(#x, __FILE__, __LINE__)

using namespace std;

static void glClearError() {
	// `GL_NO_ERROR` is guaranteed to be 0
	while (glGetError() != GL_NO_ERROR) {}
}

static void glLogError(
	const char *function,
	const char *file,
	int line
) {
	// Will keep running unless `error` variable is not 0
	while (GLenum error = glGetError()) {
		cout << "==========================" << '\n' <<
		"OpenGL Error: " << error << '\n' <<
		"Function: " << function << '\n' <<
		"File: " << file << ":" << line << endl;
	}
}

struct ShaderProgramSrc {
	string vertexSrc;
	string fragmentSrc;
};

static ShaderProgramSrc parseShader(
	const string &filePath
) {
	enum struct ShaderType {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};
	ifstream stream(filePath);

	if (!stream.is_open()) {
		utilsFunctions::handleError(
			"Could not find shader source file: " +
			filePath +
			'\n' +
			"Current working directory: " +
			filesystem::current_path().string()
		);
	}

	string line;
	stringstream ss[2];
	ShaderType type {ShaderType::NONE};

	while (getline(stream, line)) {
		if (line.find("#shader") != string::npos) {
			if (line.find("vertex") != string::npos) {
				type = ShaderType::VERTEX;
			} else if (line.find("fragment") != string::npos) {
				type = ShaderType::FRAGMENT;
			}
		} else {
			ss[static_cast<int>(type)] << line << '\n';
		}
	}

	return {
		ss[0].str(),
		ss[1].str()
	};
}

static unsigned int compileShader(
	unsigned int type,
	const string &shaderSrc
) {
	unsigned int shaderId {glCreateShader(type)};
	const char *cShaderSrc = shaderSrc.c_str();
	glShaderSource(shaderId, 1, &cShaderSrc, nullptr);
	glCompileShader(shaderId);
	string errMsg;

	switch (type) {
		case GL_VERTEX_SHADER:
			errMsg = "Vertex shader compilation failed";
			break;
		case GL_FRAGMENT_SHADER:
			errMsg = "Fragment shader compilation failed";
		default:
			errMsg = "Compilation failed";
	}

	utilsFunctions::handleShaderCompileError(shaderId, errMsg);

	return shaderId;
}

static unsigned int createShaders(
	const string &vertexShaderSrc,
	const string &fragmentShaderSrc
) {
	unsigned int programId {glCreateProgram()};
	unsigned int vertexShaderId {compileShader(GL_VERTEX_SHADER, vertexShaderSrc)};
	unsigned int fragmentShaderId {compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc)};

	// Link shaders to a shader program
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	glValidateProgram(programId);

	utilsFunctions::handleShaderProgramLinkError(programId, "Shader Program compilation failed");

	// Cleanup the generated shader intermediate .obj files from c++ compilation
	// Already stored inside the shader program and we no longer need them anymore
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	return programId;
}

int main(int argc, char *argv[]) {
	float vertices[] = {
        0.5f, 0.5f, 0.0f,  // Top right vertex
        0.5f, -0.5f, 0.0f,  // Bottom right vertex
		-0.5f, -0.5f, 0.0f,  // Bottom left vertex
		-0.5f, 0.5f, 0.0f   // Top left vertex
    };
    unsigned int indices[] = {
        0, 1, 3,  // First triangle
        1, 2, 3   // Second triangle
    };
	int windowWidth;
	int windowHeight;

	utilsFunctions::checkMainCommandArgs(argc, argv, windowWidth, windowHeight);
	GLFWwindow *window {utilsFunctions::initGLFW(windowWidth, windowHeight)};
	utilsFunctions::initGLAD(windowWidth, windowHeight);
	
	// The `.exe` file path will be the same regardless when executing debug or release
	// e.g. `build/Debug/FakeDoom.exe` or `build/Release/FakeDoom.exe`
	ShaderProgramSrc src {parseShader(
		filesystem::current_path().parent_path().parent_path().string() +
		"\\res\\shaders\\basic.shader"
	)};
	unsigned int programId {createShaders(src.vertexSrc, src.fragmentSrc)};
	glUseProgram(programId);

	// Uniforms are set per draw; need to be setup before `glDrawElements` or `glDrawArrays`
	// Attributes are set per vertex
	// Here we are setting a uniform variable in our fragment shader
	int location {glGetUniformLocation(programId, "uniformColor")};
	glUniform4f(location, 1.0f, 0.0f, 0.0f, 1.0f);
	float r {0.0f};
	float increment {0.05f};

	// Telling OpenGL how it should interpret the vertex data in memory and how it should connect the vertex data to the vertex shader's attributes
	unsigned int vaoId {utilsFunctions::linkVertexAttributes(vertices, sizeof(vertices), indices, sizeof(indices))};

	// Render loop
	// 1 iteration == 1 frame
    while (!glfwWindowShouldClose(window)) {
		utilsFunctions::processInput(window);
		utilsFunctions::setBackground(0.0f, 0.5f, 0.5f, 1.0f);

		if (r > 1.0f) {
			increment = -0.05f;
		} else if (r < 0.0f) {
			increment = 0.05f;
		}

		r += increment;
		
		glUniform4f(location, r, 0.0f, 0.0f, 1.0f);

		glBindVertexArray(vaoId);

		// Draws the currently bound buffer
		// If no EBO buffer (aka index buffer), then use `glDrawArrays(GL_TRIANGLES, 0, 3);`
		gLCall(glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr));

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll IO events (keys pressed/released, mouse moved etc.)
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}