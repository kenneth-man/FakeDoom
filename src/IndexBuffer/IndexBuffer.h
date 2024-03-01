#ifndef _INDEXBUFFER_
#define _INDEXBUFFER_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// aka `Element Buffer`
class IndexBuffer {
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	public:
		IndexBuffer(const unsigned int *data, unsigned int count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		inline unsigned int getCount() const {
			return m_Count;
		}
};

#endif