#ifndef _TEXTURE_
#define _TEXTURE_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include "../Renderer/Renderer.h"

using namespace std;

class Texture {
	private:
		unsigned int m_RendererID;
		string m_FilePath;
		unsigned char *m_LocalBuffer;
		int m_Width, m_Height, m_BPP;
	public:
		Texture(const string& path);
		~Texture();

		void bind(unsigned int slot = 0) const;
		void unbind() const;

		inline int getWidth() const {
			return m_Width;
		}
		inline int getHeight() const {
			return m_Height;
		}
};

#endif