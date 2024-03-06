#ifndef _VERTEXARRAY_
#define _VERTEXARRAY_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../VertexBuffer/VertexBuffer.h"
#include "../VertexBufferLayout/VertexBufferLayout.h"

// Vertex arrays tie together a vertex buffer with a 'layout' (vertices, positions, types, size...)
// Vertex array object is opengl's method of storing the vertex array state
class VertexArray {
	private:
		unsigned int m_RendererID;
	public:
		VertexArray();
		~VertexArray();

		void bind() const;
		void unbind() const;

		void addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);
};

#endif