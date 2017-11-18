#include "ComponentGraphics.h"
#include "Vertex.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../AGame/Common/Globals.h"
#include "../AGame/Manager/Camera.h"
#include "Texture.h"
#include "Shaders.h"
#include "Model.h"
#include "assimp/ai_assert.h"

ComponentGraphics::ComponentGraphics() :
	m_IsUpdateModelMatrix(false),
	m_Position(glm::vec3(0.0, 0.0, 0.0)),
	m_Scale(glm::vec3(1.0, 1.0, 1.0)),
	m_Rotate(glm::vec3(0.0, 0.0, 0.0)),
	m_ObjectColor(glm::vec3(1.0, 0.5, 0.5))
{
}

ComponentGraphics::~ComponentGraphics()
{
}

void ComponentGraphics::Render(float dt)
{
	m_Shader->Use();
	glBindBuffer(GL_ARRAY_BUFFER, m_Model->GetVboID());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Model->GetIboID());
	
	//connect position
	GLuint p = m_Shader->GetAttributeLocation("a_position");
	if (p != -1)
	{
		glEnableVertexAttribArray(p);
		glVertexAttribPointer(p, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, pos)));
	}
	//connect normal
	p = m_Shader->GetAttributeLocation("a_normal");
	if (p != -1)
	{
		glEnableVertexAttribArray(p);
		glVertexAttribPointer(p, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, nor)));
	}
	//connect color
	p = m_Shader->GetAttributeLocation("a_color");
	if (p != -1)
	{
		glEnableVertexAttribArray(p);
		glVertexAttribPointer(p, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));
	}
	//connect uv coordinate
	p = m_Shader->GetAttributeLocation("a_uv");
	if (p != -1)
	{
		glEnableVertexAttribArray(p);
		glVertexAttribPointer(p, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uv)));
	}

	//lighting stuff
	m_Shader->SetVec3("u_lightViewPos", CameraMgr->GetPosition());

	//directional light
	m_Shader->SetVec3("u_dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	m_Shader->SetVec3("u_dirLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	m_Shader->SetVec3("u_dirLight.diffuse", glm::vec3(0.9f, 0.9f, 0.9f));
	m_Shader->SetVec3("u_dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

	//point lights
	for (int i=0; i<Globals::s_NumPointLights; i++)
	{
		std::string nl = std::string("u_pointLights[") + std::to_string(i) + std::string("].");
		m_Shader->SetVec3(nl + std::string("position"), Globals::s_PointLightPos[i]);
		m_Shader->SetVec3(nl + std::string("ambient"), glm::vec3(0.2f, 0.2f, 0.2f));
		m_Shader->SetVec3(nl + std::string("diffuse"), glm::vec3(0.9f, 0.9f, 0.9f));
		m_Shader->SetVec3(nl + std::string("specular"), glm::vec3(1.0f, 1.0f, 1.0f));
		m_Shader->SetFloat(nl + std::string("constant"), 1.0f);
		m_Shader->SetFloat(nl + std::string("linear"), 0.09f);
		m_Shader->SetFloat(nl + std::string("quadratic"), 0.032f);
	}

	//spot light
	m_Shader->SetVec3("u_spotLight.position", CameraMgr->GetPosition());
	m_Shader->SetVec3("u_spotLight.direction", CameraMgr->GetFront());
	m_Shader->SetVec3("u_spotLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	m_Shader->SetVec3("u_spotLight.diffuse", glm::vec3(0.9f, 0.9f, 0.9f));
	m_Shader->SetVec3("u_spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	m_Shader->SetFloat("u_spotLight.constant",  1.0f);
	m_Shader->SetFloat("u_spotLight.linear",    0.09f);
	m_Shader->SetFloat("u_spotLight.quadratic", 0.032f);
	m_Shader->SetFloat("u_spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	m_Shader->SetFloat("u_spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));

	//m_Shader->SetVec3("u_material.ambient", glm::vec3(0.0215f, 0.1745f, 0.0215f));
	//m_Shader->SetVec3("u_material.diffuse", glm::vec3(0.07568f, 0.61424f, 0.07568f)); //use texture diffuse instead
	//m_Shader->SetVec3("u_material.specular", glm::vec3(0.633f, 0.727811f, 0.633f)); //use texture specular instead
	m_Shader->SetFloat("u_material.shininess", 64.0f);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture->GetTextureID());//bind diffuse map
	m_Shader->SetInt("u_material.diffuse", 0);//connect diffuse map
	if (m_Textures.size() > 1)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_Textures[1]->GetTextureID());//bind specular map
		m_Shader->SetInt("u_material.specular", 1);//connect diffuse map
	}
		
	static float test_theta = 0.0f;
	test_theta += 0.0f * dt;
//	Globals::s_LightPosition.x = float(glm::sin(glm::radians(test_theta)));
	//Globals::s_LightPosition.z = float(glm::cos(glm::radians(test_theta)));
	
	m_Shader->SetMatrix4("u_model", m_ModelMatrix);
	m_Shader->SetMatrix4("u_view", m_ViewMatrix);
	m_Shader->SetMatrix4("u_projection", m_PerspectiveMatrix);
	glm::mat3 a = glm::mat3(m_ModelMatrix);
	m_Shader->SetMatrix4("u_tranposeAndInverseModel", glm::transpose(glm::inverse(m_ModelMatrix)));

	//connect texture
	m_Shader->SetInt("u_texture", 0);
	
	glDrawArrays(GL_TRIANGLES, 0, m_Model->GetNumVertices());
//	glDrawElements(GL_TRIANGLES, m_Model->GetNumIndices(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ComponentGraphics::Update(float dt)
{
	if(m_IsUpdateModelMatrix){
		glm::mat4 trans;
		trans = glm::translate(trans, m_Position);
		trans = glm::scale(trans, m_Scale);
		trans = glm::rotate(trans, glm::radians(m_Rotate[0]), glm::vec3(1.0, 0.0, 0.0));
		trans = glm::rotate(trans, glm::radians(m_Rotate[1]), glm::vec3(0.0, 1.0, 0.0));
		trans = glm::rotate(trans, glm::radians(m_Rotate[2]), glm::vec3(0.0, 0.0, 1.0));
		m_ModelMatrix = trans;
		m_IsUpdateModelMatrix = false;
	}
	m_ViewMatrix = CameraMgr->GetLookAtMatrix();
	m_PerspectiveMatrix = CameraMgr->GetPerspectiveMatrix();
}

std::shared_ptr<Model> ComponentGraphics::GetModel() const
{
	return m_Model;
}

void ComponentGraphics::SetModel(std::shared_ptr<Model> model)
{
	m_Model = model;
}

std::shared_ptr<Shaders> ComponentGraphics::GetShader() const
{
	return m_Shader;
}

void ComponentGraphics::SetShader(std::shared_ptr<Shaders> shader)
{
	m_Shader = shader;
}

std::shared_ptr<Texture> ComponentGraphics::GetTexture() const
{
	return m_Texture;
}

void ComponentGraphics::SetTexture(std::shared_ptr<Texture> texture)
{
	m_Texture = texture;
	if (m_Textures.size() == 0)
	{
		m_Textures.push_back(texture);
	}
}

void ComponentGraphics::AddTexture(std::shared_ptr<Texture> t)
{
	m_Textures.push_back(t);
}
