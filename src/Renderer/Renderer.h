#ifndef _RENDERER_
#define _RENDERER_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../VertexArray/VertexArray.h"
#include "../IndexBuffer/IndexBuffer.h"
#include "../Shader/Shader.h"

using namespace std;

class Renderer {
	private:
	public:
		Renderer();
		~Renderer();

		void draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
		void clear() const;
		void setBackground(float r, float g, float b, float a) const;
};

#endif