#pragma once
#include "../Common/Singleton.hpp"
#include <glm/detail/type_vec2.hpp>

#define KEY_FORWARD (1 << 1)
#define KEY_BACKWARD (1 << 2)
#define KEY_LEFT (1 << 3)
#define KEY_RIGHT (1 << 4)

class ManagerInput
{
public:
	ManagerInput();
	~ManagerInput();

	void SetKeyPressed(int key, bool isPress=true);
	bool IsPressed(int key) const;
	void ClearKeys();
	void SetTouchPos(glm::vec2 pos);
	glm::vec2 GetTouchPos() const;
	void SetLastTouchPos(glm::vec2 pos);
	glm::vec2 GetLastTouchPos() const;

	void SetIsFirstTouch(bool v) { m_IsFirstTouch = v; }
	bool IsFirstTouch() const { return m_IsFirstTouch; }
private:
	int m_Keys;
	glm::vec2 m_TouchPos;
	glm::vec2 m_LastTouchPos;
	bool m_IsFirstTouch;
};

typedef Singleton<ManagerInput> SingletonManagerInput;
#define InputMgr SingletonManagerInput::GetInstance()