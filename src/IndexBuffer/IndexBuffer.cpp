#include "IndexBuffer.h"

// When you pass a C array, you're passing a pointer/memory address to its first element (since true C arrays don't exist)
// Meaning you're not actually passing the entire array; so the argument decays into a pointer to its first element
IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count)
	: m_Count(count)
{
	// Generate index buffer and insert data into it with same size as `indicesSize`
	// Index buffers are used index the vertex buffer, allowing us to re-use existing vertices, limiting amount of GPU needed (duplicate vertices require more memory)
	// Index buffers MUST be made up of unsigned integers, that's why `*data` is `unsigned int` and not `void`; also why we pass in `count` rather than `size`
    glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}