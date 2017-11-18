#include "stdafx.h"
#include "Shaders.h"
#include <glm/gtc/type_ptr.hpp>

Shaders::Shaders():
	m_ID(0)
{

}

Shaders::Shaders(GLint id):
	m_ID(id)
{
}

GLint Shaders::GetAttributeLocation(const std::string & name) const
{
	return glGetAttribLocation(m_Program, name.c_str());
}

GLint Shaders::GetUniformLocation(const std::string & name) const
{
	return glGetUniformLocation(m_Program, name.c_str());
}

void Shaders::SetBool(const std::string & name, bool value) const
{
	GLuint p = GetUniformLocation(name);
	if (p != -1)
	{
		glUniform1i(p, int(value));
	}
}

void Shaders::SetInt(const std::string & name, int value) const
{
	GLuint p = GetUniformLocation(name);
	if (p != -1)
	{
		glUniform1i(p, value);
	}
}

void Shaders::SetFloat(const std::string & name, float value) const
{
	GLuint p = GetUniformLocation(name);
	if (p != -1)
	{
		glUniform1f(p, value);
	}	
}

void Shaders::SetMatrix4(const std::string & name, glm::mat4 value) const
{
	GLuint p = GetUniformLocation(name);
	if (p != -1)
	{
		glUniformMatrix4fv(p, 1, GL_FALSE, glm::value_ptr(value));
	}	
}

void Shaders::SetMatrix3(const std::string& name, glm::mat3 value) const
{
	GLuint p = GetUniformLocation(name);
	if (p != -1)
	{
		glUniformMatrix3fv(p, 1, GL_FALSE, glm::value_ptr(value));
	}
}

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	m_VertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if (m_VertexShader == 0)
		return -1;

	m_FragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if (m_FragmentShader == 0)
	{
		glDeleteShader(m_VertexShader);
		return -2;
	}
	m_Program = esLoadProgram(m_VertexShader, m_FragmentShader);
	return 0;
}

void Shaders::Use()
{
	glUseProgram(m_Program);
}

void Shaders::SetVec3(const std::string& name, glm::vec3 value) const
{
	glUniform3fv(GetUniformLocation(name), 1, &value[0]);
}

void Shaders::SetVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(GetUniformLocation(name), x, y, z);
}

Shaders::~Shaders()
{
	glDeleteProgram(m_Program);
	glDeleteShader(m_VertexShader);
	glDeleteShader(m_FragmentShader);
}
