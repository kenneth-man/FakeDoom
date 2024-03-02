#ifndef _VERTEXBUFFER_
#define _VERTEXBUFFER_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex buffers are just areas of memory (on GPU) that contain data (bytes), usually vertex data attributes (positions, normals, texture coords...)
// They have no concept of the meaning of the data 
// Stored in GPU memory so prevents GPU-CPU communication bottleneck, improve efficiency
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