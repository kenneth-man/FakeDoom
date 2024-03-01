#ifndef _VERTEXBUFFER_
#define _VERTEXBUFFER_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer {
	private:
		unsigned int m_RendererID;
	public:
		VertexBuffer(const void *data, size_t size);
		~VertexBuffer();

		void bind() const;
		void unbind() const;
};

#endif