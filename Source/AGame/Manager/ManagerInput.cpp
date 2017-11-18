#include "ManagerInput.h"

ManagerInput::ManagerInput():
	m_Keys(0),
	m_IsFirstTouch(true)
{
}

ManagerInput::~ManagerInput()
{
}

void ManagerInput::SetKeyPressed(int key, bool isPress)
{
	if (isPress)
	{
		m_Keys |= key;
	}
	else
	{
		m_Keys &= ~key;
	}
}

bool ManagerInput::IsPressed(int key) const
{
	return m_Keys & key;
}

void ManagerInput::ClearKeys()
{
	m_Keys = 0;
}

void ManagerInput::SetTouchPos(glm::vec2 pos)
{
	m_TouchPos = pos;
}

glm::vec2 ManagerInput::GetTouchPos() const
{
	return m_TouchPos;
}

void ManagerInput::SetLastTouchPos(glm::vec2 pos)
{
	m_LastTouchPos = pos;
}

glm::vec2 ManagerInput::GetLastTouchPos() const
{
	return m_LastTouchPos;
}
