#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
	: m_Stride(0)
{}

void VertexBufferLayout::push(
	unsigned int glTypeMacro,
	unsigned int count,
	unsigned char normalised
) {
	m_Elements.push_back({
		glTypeMacro,
		count,
		normalised
	});
	m_Stride += count * sizeof(VertexBufferElement::getSizeOfType(glTypeMacro));
}