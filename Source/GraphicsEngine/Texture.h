#pragma once
#include <GLES2/gl2.h>

class Texture
{
public:
	Texture();
	explicit Texture(int ID);
	~Texture();
	GLuint GetTextureID() const;
	void LoadFile(const char* filePath);
private:
	GLuint m_ID;
	GLuint m_TextureID;
	static void SetTextureParamerter();
};