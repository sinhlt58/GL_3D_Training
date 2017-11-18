#include "stb_lib/stb_image.hpp"
#include "Texture.h"

Texture::Texture():m_ID(0),
				   m_TextureID(0)	
{
}

Texture::Texture(int ID):m_ID(ID),
					m_TextureID(0)
{
}

Texture::~Texture()
{
}

GLuint Texture::GetTextureID() const
{
	return m_TextureID;
}

void Texture::LoadFile(const char* filePath)
{
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	int width, height, bpp;
	unsigned char* imageData = stbi_load(filePath, &width, &height, &bpp, 0);
	GLenum internalFormat = (bpp == 3) ? GL_RGB : GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, imageData);
	SetTextureParamerter();
	glBindTexture(GL_TEXTURE_2D, 0);
	if (imageData) delete[] imageData;
}

void Texture::SetTextureParamerter()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
