#pragma once
#include "../Common/Singleton.hpp"
#include <glm/mat4x4.hpp>

class Camera
{
public:
	Camera();

	glm::vec3 GetPosition() const;
	void SetPosition(glm::vec3 pos);
	glm::vec3 GetFront() const;
	void SetFront(glm::vec3 v);
	glm::vec3 GetUp() const;
	void SetUp(glm::vec3 v);
	glm::mat4 GetLookAtMatrix() const;
	void UpdateLookAtMatrix();
	glm::mat4 GetPerspectiveMatrix() const;
	void UpdatePerspectiveMatrix();

	float GetFOV()const { return m_Fov; }
	float GetNear()const { return m_Near; }
	float GetFar()const { return m_Far; }
	float GetAspectRation()const { return m_AspectRatio; }
	void SetFOV(float f);
	void SetNear(float f);
	void SetFar(float f);
	void SetAspectRation(float f);

	void Init();

	void SetSpeed(float s) { m_Speed = s; }
	float GetSpeed() const { return m_Speed; }
	void MoveLeft();
	void MoveRight();
	void MoveForWard();
	void MoveBackWard();

	void UpdateRotationFPS();
	float GetSensitivity() const { return m_Sensitivity; }
	void SetSensitivity(float s) { m_Sensitivity = s; }
private:
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::mat4 m_LookAtMatrix;
	glm::mat4 m_PerspectiveMatrix;

	float m_Fov;
	float m_Near;
	float m_Far;
	float m_AspectRatio;

	float m_Speed;

	float m_Pitch;
	float m_Yaw;
	float m_Roll;
	float m_Sensitivity;
};

typedef Singleton<Camera> SingletonCamera;
#define CameraMgr SingletonCamera::GetInstance()