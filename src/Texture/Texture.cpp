#include "./Texture.h"

Texture::Texture(const string& path)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr),
		m_Width(0), m_Height(0), m_BPP(0)
{
	// Flips texture vertically
	// Opengl expects texture pixels to start at bottom left, not top left (.png)
	stbi_set_flip_vertically_on_load(1);

	// Load texture data into local buffer
	// Passing pointers/addresses to `stbi_load` so it can write to them
	// `4` channels for rgba
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	// Settings for the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Specify a two-dimensional texture image
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA8,
		m_Width,
		m_Height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		m_LocalBuffer
	);

	// Unbind texture
	// Each architecture has a limit to how many textures can be bound at the same time
	// Best to unbind if don't need anymore
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBuffer) {
		// Could use the buffer data for anything else, but we don't need it
		stbi_image_free(m_LocalBuffer);
	}

}

Texture::~Texture() {
	// Delete the texture from the GPU
	glDeleteTextures(1, &m_RendererID);
}

void Texture::bind(unsigned int slot) const {
	// Set the slot we want to bind our next texture to
	// `GL_TEXTURE0` is the first texture slot
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}
