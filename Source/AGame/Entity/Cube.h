#pragma once
#include <memory>
#include <vector>

class ComponentGraphics;

class Cube
{
public:
	Cube();
	virtual ~Cube();
	void Init();
	void Update(float dt);
	void Render(float dt);
	std::shared_ptr<ComponentGraphics> GetComponentGraphics() const;
	void SetComponentGraphics(std::shared_ptr<ComponentGraphics> c);
private:
	std::shared_ptr<ComponentGraphics> m_ComGrahpics;
};