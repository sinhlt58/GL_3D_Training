#pragma once
#include <GLES2/gl2.h>

class Model
{
public:
	Model();
	Model(int ID);
	~Model();
	void LoadModel(const char* filePath);
	GLuint GetVboID() const;
	GLuint GetIboID() const;
	GLuint GetNumVertices() const;
	GLuint GetNumIndices() const;
private:
	GLuint m_ID;
	GLuint m_VboID;
	GLuint m_IboID;
	GLuint m_NumVertices;
	GLuint m_NumIndices;
};
