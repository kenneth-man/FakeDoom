#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include "./src/utils/functions/functions.h"
#include "./src/IndexBuffer/IndexBuffer.h"
#include "./src/VertexBuffer/VertexBuffer.h"
#include "./src/VertexArray/VertexArray.h"
#include "./src/Shader/Shader.h"
#include "./src/Renderer/Renderer.h"
#include "./src/Texture/Texture.h"

using namespace std;

int main(int argc, char *argv[]) {
	float vertices[] = {
		// Top right vertex
		0.5f, 0.5f,// 0.0f,
			// Top right vertex texture coordinates
			1.0f, 1.0f,
		// Bottom right vertex
		0.5f, -0.5f,// 0.0f,
			1.0f, 0.0f,
		// Bottom left vertex
		-0.5f, -0.5f,// 0.0f,
			0.0f, 0.0f,
		// Top left vertex
		-0.5f, 0.5f,// 0.0f,
			0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 3,  // First triangle
		1, 2, 3   // Second triangle
	};
	int windowWidth;
	int windowHeight;
	float r {0.0f};
	float increment {0.05f};
	string rootDir {filesystem::current_path()
		.parent_path().parent_path().parent_path().parent_path().string()};

	utilsFunctions::checkMainCommandArgs(argc, argv, windowWidth, windowHeight);
	GLFWwindow *window {utilsFunctions::initGLFW(windowWidth, windowHeight)};
	utilsFunctions::initGLAD(windowWidth, windowHeight);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	VertexArray va;
	VertexBuffer vb {vertices, sizeof(vertices)};
	VertexBufferLayout layout;

	// `3` because we intend that each vertex consists of 3 floats (xyz positions)
	layout.push(GL_FLOAT, 2, GL_FALSE);
	layout.push(GL_FLOAT, 2, GL_FALSE);
	va.addBuffer(vb, layout);

	IndexBuffer ib {indices, sizeof(indices) / sizeof(indices[0])};

	// The `.exe` file path will be the same regardless whether executing debug or release
	// e.g. `build/Debug/FakeDoom.exe` or `build/Release/FakeDoom.exe`
	Shader shader(rootDir + "\\res\\shaders\\basic.shader");

	shader.bind();
	shader.setUniform4f("uniformColor", r, 0.0f, 0.0f, 1.0f); // "u_Color"
	va.unbind();
	vb.unbind();
	ib.unbind();
	shader.unbind();

	Texture texture(rootDir + "\\res\\textures\\bricks.png");

	// Our `bind` method binds a texture to slot 0 by default if no args
	// `setUniform1i` slot should match the same slot
	texture.bind();
	shader.setUniform1i("u_Texture", 0);

	Renderer renderer;

	// Render loop; 1 iteration == 1 frame
	while (!glfwWindowShouldClose(window)) {
		utilsFunctions::processInput(window);
		renderer.clear();
		renderer.setBackground(0.0f, 0.5f, 0.5f, 1.0f);

		shader.bind();
		shader.setUniform4f("uniformColor", r, 0.0f, 0.0f, 1.0f); // "u_Color"

		renderer.draw(va, ib, shader);

		if (r > 1.0f) {
			increment = -0.05f;
		}
		else if (r < 0.0f) {
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