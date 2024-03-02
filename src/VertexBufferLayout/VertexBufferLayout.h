#ifndef _VERTEXBUFFERLAYOUT_
#define _VERTEXBUFFERLAYOUT_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

using namespace std;

struct VertexBufferElement {
	 // GL_FLOAT, GL_UNSIGNED_INT, GL_UNSIGNED_BYTE...
	unsigned int type;
	unsigned int count;
	 //GL_FALSE, GL_TRUE
	unsigned char normalised;

	static unsigned int getSizeOfType(unsigned int type) {
		switch (type) {
			case GL_FLOAT:
				return 4;
			case GL_UNSIGNED_INT:
				return 4;
			case GL_UNSIGNED_BYTE:
				return 1;
			default:
				return 0;
		}
	}
};

class VertexBufferLayout {
	private:
		vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
	public:
		VertexBufferLayout();

		void push(
			unsigned int glTypeMacro,
			unsigned int count,
			unsigned char normalised
		);

		inline const vector<VertexBufferElement> getElements() const {
			return m_Elements;
		};

		inline unsigned int getStride() const {
			return m_Stride;
		};
};

#endif