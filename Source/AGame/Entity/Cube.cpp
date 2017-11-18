#include "Cube.h"
#include "GraphicsEngine\ComponentGraphics.h"

Cube::Cube()
{

}

Cube::~Cube()
{
}

void Cube::Init()
{
	m_ComGrahpics = std::make_shared<ComponentGraphics>();
}

void Cube::Update(float dt)
{
	m_ComGrahpics->Update(dt);
}

void Cube::Render(float dt)
{
	m_ComGrahpics->Render(dt);
}

std::shared_ptr<ComponentGraphics> Cube::GetComponentGraphics() const
{
	return m_ComGrahpics;
}

void Cube::SetComponentGraphics(std::shared_ptr<ComponentGraphics> c)
{
	m_ComGrahpics = c;
}
