#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <string>
#include "./src/utils/functions/functions.h"

using namespace std;

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

	// link shaders to a shader program
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	glValidateProgram(programId);

	utilsFunctions::handleShaderProgramLinkError(programId, "Shader Program compilation failed");

	// cleanup the generated shader intermediate .obj files from c++ compilation
	// already stored inside the shader program and we no longer need them anymore
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	return programId;
}

int main(int argc, char *argv[]) {
	float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right vertex
         0.5f, -0.5f, 0.0f,  // bottom right vertex
        -0.5f, -0.5f, 0.0f,  // bottom left vertex
        -0.5f,  0.5f, 0.0f   // top left vertex
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
	
	// the `.exe` file path will be the same regardless when executing debug or release
	// e.g. `build/Debug/FakeDoom.exe` or `build/Release/FakeDoom.exe`
	ShaderProgramSrc src {parseShader(
		filesystem::current_path().parent_path().parent_path().string() +
		"\\res\\shaders\\basic.shader"
	)};
	unsigned int programId {createShaders(src.vertexSrc, src.fragmentSrc)};
	glUseProgram(programId);
	// telling OpenGL how it should interpret the vertex data in memory and how it should connect the vertex data to the vertex shader's attributes
	unsigned int vaoId {utilsFunctions::linkVertexAttributes(vertices, sizeof(vertices), indices, sizeof(indices))};

	// render loop
	// 1 iteration == 1 frame
    while (!glfwWindowShouldClose(window)) {
		utilsFunctions::processInput(window);
		utilsFunctions::setBackground(0.0f, 0.5f, 0.5f, 1.0f);

		glBindVertexArray(vaoId);

		// draws the currently bound buffer
		// if no EBO buffer (aka index buffer), then use `glDrawArrays(GL_TRIANGLES, 0, 3);`
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll IO events (keys pressed/released, mouse moved etc.)
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}