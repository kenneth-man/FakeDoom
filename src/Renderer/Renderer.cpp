#include "Renderer.h"

Renderer::Renderer() {
}

Renderer::~Renderer() {
}

void Renderer::draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const {
	va.bind();
	ib.bind();
	shader.bind();
	// Draws the currently bound buffer
	// If no Index buffer (aka element buffer), then use `glDrawArrays(GL_TRIANGLES, ...);`
	glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::clear() const {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::setBackground(float r, float g, float b, float a) const {
	glClearColor(r, g, b, a);
}