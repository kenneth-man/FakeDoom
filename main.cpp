#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>
// #include <fstream>
#include <filesystem>
// #include <sstream>
// #include <string>
#include <variant>
#include "functions.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

using namespace std;

int main(int argc, char *argv[]) {
	cout << __cplusplus << endl;
	std::variant<int, double> v;

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
	float r {0.0f};
	float increment {0.05f};

	utilsFunctions::checkMainCommandArgs(argc, argv, windowWidth, windowHeight);
	GLFWwindow *window {utilsFunctions::initGLFW(windowWidth, windowHeight)};
	utilsFunctions::initGLAD(windowWidth, windowHeight);
	VertexArray va;
	VertexBuffer vb {vertices, sizeof(vertices)};
	VertexBufferLayout layout;

	// `3` because we intend that each vertex consists of 3 floats (xyz positions)
	layout.push(GL_FLOAT, 3, GL_FALSE);
	va.addBuffer(vb, layout);

	IndexBuffer ib {indices, sizeof(indices) / sizeof(indices[0])};

	// The `.exe` file path will be the same regardless whether executing debug or release
	// e.g. `build/Debug/FakeDoom.exe` or `build/Release/FakeDoom.exe`
	Shader shader(
		filesystem::current_path().parent_path().parent_path().string() +
		"\\res\\shaders\\basic.shader"
	);
	// shader.bind();
	// shader.setUniform4f("uniformColor", r, 0.0f, 0.0f, 1.0f); // "u_Color"
	// va.unbind();
	// vb.unbind();
	// ib.unbind();
	// shader.unbind();

	// Render loop; 1 iteration == 1 frame
	while (!glfwWindowShouldClose(window)) {
		utilsFunctions::processInput(window);
		utilsFunctions::setBackground(0.0f, 0.5f, 0.5f, 1.0f);

		shader.bind();
		shader.setUniform4f("uniformColor", r, 0.0f, 0.0f, 1.0f); // "u_Color"

		va.bind();
		ib.bind();

		// Draws the currently bound buffer
		// If no EBO buffer (aka index buffer), then use `glDrawArrays(GL_TRIANGLES, 0, 3);`
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr);

		if (r > 1.0f) {
			increment = -0.05f;
		} else if (r < 0.0f) {
			increment = 0.05f;
		}

		r += increment;

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll IO events (keys pressed/released, mouse moved etc.)
		glfwPollEvents();
	}

    glfwTerminate();

    return 0;
}