#pragma once
#include <GLES2/gl2.h>
#include <string>

class Texture
{
public:
	Texture();
	explicit Texture(int ID);
	~Texture();
	GLuint GetTextureID() const;
	void LoadFile(const char* filePath);
	void SetType(std::string s) { m_Type = s; }
	std::string GetType() const { return m_Type; }
private:
	GLuint m_ID;
	GLuint m_TextureID;
	std::string m_Type;
	static void SetTextureParamerter();
};
