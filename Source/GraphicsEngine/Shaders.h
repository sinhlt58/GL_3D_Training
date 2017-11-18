#pragma once
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <GLES2/gl2.h>

class Shaders
{
public:
	Shaders();
	Shaders(GLint id);
	~Shaders();
	
	GLint GetID() const { return m_ID; }
	int Init(char * fileVertexShader, char * fileFragmentShader);
	void Use();

	GLint GetAttributeLocation(const std::string &name) const;
	GLint GetUniformLocation(const std::string &name) const;
	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;
	void SetMatrix4(const std::string &name, glm::mat4 value) const;
	void SetMatrix3(const std::string &name, glm::mat3 value) const;
	void SetVec3(const std::string &name, glm::vec3 value) const;
	void SetVec3(const std::string &name, float x, float y, float z) const;

private:
	GLuint m_ID;
	GLuint m_Program;
	GLuint m_VertexShader;
	GLuint m_FragmentShader;
};