#include "Camera.h"
#include <glm/gtc/matrix_transform.inl>
#include "AGame/Common/Globals.h"
#include "ManagerInput.h"

void Camera::Init()
{

}

Camera::Camera():
	m_Position(glm::vec3(0.0f, 0.0f, 5.0f)),
	m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
	m_Up(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_Fov(glm::radians(45.0f)),
	m_Near(0.1f),
	m_Far(100.0f),
	m_AspectRatio(float(Globals::screenWidth/Globals::screenHeight)),
	m_Speed(300.0f),
	m_Pitch(0.0f),
	m_Yaw(0.0f),
	m_Roll(0.0f),
	m_Sensitivity(0.1f)
{
	UpdateLookAtMatrix();
	UpdatePerspectiveMatrix();
}

void Camera::MoveLeft()
{
	m_Position += glm::normalize(glm::cross(m_Up, m_Front)) * m_Speed * Globals::s_DeltaTime;
	UpdateLookAtMatrix();
}

void Camera::MoveRight()
{
	m_Position -= glm::normalize(glm::cross(m_Up, m_Front)) * m_Speed * Globals::s_DeltaTime;
	UpdateLookAtMatrix();
}

void Camera::MoveForWard()
{
	m_Position += m_Speed * Globals::s_DeltaTime * m_Front;
	UpdateLookAtMatrix();
}

void Camera::MoveBackWard()
{
	m_Position -= m_Speed * Globals::s_DeltaTime * m_Front;
	UpdateLookAtMatrix();
}

glm::vec3 Camera::GetPosition() const
{
	return m_Position;
}

void Camera::SetPosition(glm::vec3 pos)
{
	m_Position = pos;
}

glm::vec3 Camera::GetFront() const
{
	return m_Front;
}

void Camera::SetFront(glm::vec3 v)
{
	m_Front = v;
}

glm::vec3 Camera::GetUp() const
{
	return m_Up;
}

void Camera::SetUp(glm::vec3 v)
{
	m_Up = v;
}

glm::mat4 Camera::GetLookAtMatrix() const
{
	return m_LookAtMatrix;
}

void Camera::UpdateLookAtMatrix()
{
	m_LookAtMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

glm::mat4 Camera::GetPerspectiveMatrix() const
{
	return m_PerspectiveMatrix;
}

void Camera::UpdatePerspectiveMatrix()
{
	m_PerspectiveMatrix = glm::perspective(m_Fov, m_AspectRatio, m_Near, m_Far);
}


void Camera::SetFOV(float f)
{
	m_Fov = f;
}

void Camera::SetNear(float f)
{
	m_Near = f;
}

void Camera::SetFar(float f)
{
	m_Far = f;
}

void Camera::SetAspectRation(float f)
{
	m_AspectRatio = f;
}

void Camera::UpdateRotationFPS()
{
	glm::vec2 lastPos = InputMgr->GetLastTouchPos();
	glm::vec2 currPos = InputMgr->GetTouchPos();

	m_Pitch += -(currPos.y - lastPos.y) * m_Sensitivity;
	m_Yaw += (currPos.x - lastPos.x) * m_Sensitivity;

	if (m_Pitch >  89) m_Pitch = 89;
	if (m_Pitch < -89) m_Pitch = -89;
 
	glm::vec3 front;
	front.y = sin(glm::radians(m_Pitch));
	front.x = cos(glm::radians(m_Pitch))*sin(glm::radians(m_Yaw));
	front.z = -cos(glm::radians(m_Pitch))*cos(glm::radians(m_Yaw));
	if (glm::length(front) > 0)
	{
		m_Front = glm::normalize(front);
		UpdateLookAtMatrix();
	}
}
