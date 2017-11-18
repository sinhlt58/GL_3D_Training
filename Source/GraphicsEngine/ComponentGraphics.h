#pragma once
#include <memory>
#include <glm/mat4x4.hpp>
#include <vector>

class Model;
class Shaders;
class Texture;

class ComponentGraphics
{
public:
	ComponentGraphics();
	~ComponentGraphics();

	void Render(float dt);
	void Update(float dt);

	std::shared_ptr<Model> GetModel() const;
	void SetModel(std::shared_ptr<Model> model);
	std::shared_ptr<Shaders> GetShader() const;
	void SetShader(std::shared_ptr<Shaders> shader);
	std::shared_ptr<Texture> GetTexture() const;
	void SetTexture(std::shared_ptr<Texture> texture);
	void SetUpdateModelMatrix(bool v) { m_IsUpdateModelMatrix = v; };
	bool GetUpdateModelMatrix()const { return m_IsUpdateModelMatrix; }

	void SetPosition(const glm::vec3 &pos) { m_Position = pos; m_IsUpdateModelMatrix = true; };
	glm::vec3 GetPosition() const { return m_Position; }
	void SetScale(const glm::vec3 &s) { m_Scale = s; m_IsUpdateModelMatrix = true;};
	glm::vec3 GetScale() const { return m_Scale; }
	void SetRotate(const glm::vec3 &r) { m_Rotate = r; m_IsUpdateModelMatrix = true;};
	glm::vec3 GetRotate() const { return m_Rotate; }
	void SetObjectColor(const glm::vec3 &c){m_ObjectColor = c; }
	glm::vec3 GetObjectColor() const { return m_ObjectColor; }

	//tmp might remove later
	void AddTexture(std::shared_ptr<Texture> t);
	
private:
	std::shared_ptr<Model> m_Model;
	std::shared_ptr<Shaders> m_Shader;
	std::shared_ptr<Texture> m_Texture;
	std::vector<std::shared_ptr<Texture>> m_Textures;
	glm::mat4 m_ModelMatrix;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_PerspectiveMatrix;

	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::vec3 m_Rotate;
	bool m_IsUpdateModelMatrix;

	//lighting stuff
	glm::vec3 m_ObjectColor;
};