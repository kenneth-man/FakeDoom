#include "VertexArray.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_RendererID);

	// Uncomment this call to draw in wireframe polygons
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::bind() const {
	glBindVertexArray(m_RendererID);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}

void VertexArray::addBuffer(
	const VertexBuffer &vb,
	const VertexBufferLayout &layout
) {
	bind();
	vb.bind();

	// 'layout' setup for vertex buffer/s
	const auto &elements {layout.getElements()};

	for (unsigned int i {0}; i < elements.size(); ++i) {
		const auto &element {elements[i]};
		unsigned int offset {0};

		// Disable compile warning: type cast conversion from 'unsigned int' to 'const void *' of greater size
		// In OpenGL, it's a common practice to use an offset (often represented as an integer) to specify where in the buffer the data for a particular attribute begins
		// It's saying that you are casting from an `unsigned int` to a `const void*`, and on some platforms, a `const void*` might be larger than an `unsigned int`
		#pragma warning(push)
		#pragma warning(disable : 4312)
		// Setup how opengl should interpret what consitutes as a vertex from our buffer data in `glBufferData`; `glVertexAttribPointer` links vertex array with the currently bound vertex buffer
		// 5th arg is `stride` which is the amount of bytes between each vertex (size of each vertex); so that opengl knows how many bytes to jump in the buffer to the next vertex
		// 6th arg is `pointer` which is the offset in bytes of the attributes in a vertex; e.g. A single vertex may have attributes: position, texture coordinate, normal
			// `pointer` is the offset of those in bytes in the buffer; e.g. position (offset is 0 since it's first), texture coordinate (12 bytes forward/offset), normal (20 bytes)...
		glVertexAttribPointer(
			i,
			element.count,
			element.type,
			element.normalised,
			layout.getStride(),
			(const void*)offset
		);
		#pragma warning(pop)

		glEnableVertexAttribArray(i);

		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
}